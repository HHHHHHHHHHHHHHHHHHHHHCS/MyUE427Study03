// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyNormal_Controller.h"

#include "EnemyNormal.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

AEnemyNormal_Controller::AEnemyNormal_Controller()
{
	navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
}

void AEnemyNormal_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	enemyPawn = Cast<AEnemyNormal>(InPawn);
	animInst = enemyPawn->GetMesh()->GetAnimInstance();
	enemyPawn->GetCharacterMovement()->MaxWalkSpeed = patrolWalkSpeed;
}

void AEnemyNormal_Controller::Patrol()
{
	if (!navSys)
	{
		return;
	}

	const float searchRadius = 1000.0f;
	FNavLocation randomLocation;
	bool isFound = navSys->GetRandomReachablePointInRadius(enemyPawn->GetActorLocation(), searchRadius, randomLocation);
	if (isFound)
	{
		MoveToLocation(randomLocation);
	}
}

void AEnemyNormal_Controller::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (bisRunningBack)
	{
		bisRunningBack = false;
		bIsPatrolling = true;
		enemyPawn->GetCharacterMovement()->MaxWalkSpeed = patrolWalkSpeed;
	}

	if (GetIsInAttackRange())
	{
		PerformAttack();
		return;
	}

	if (bIsPatrolling)
	{
		float thinkTime = FMath::RandRange(1.0f, 4.0f);
		GetWorldTimerManager().SetTimer(timerHandle_Patrol, this, &AEnemyNormal_Controller::DetectedPool, thinkTime, false);
	}
}

void AEnemyNormal_Controller::DetectedPool()
{
	if (bIsPatrolling)
	{
		Patrol();
	}
}

int AEnemyNormal_Controller::GetNextAnimationIndex()
{
	int idx;
	if (enemyPawn->attackAnimMontages.Num() == 0)
	{
		idx = 0;
	}
	else
	{
		idx = (currAttackIndex + 1) % enemyPawn->attackAnimMontages.Num();
	}

	return idx;
}

bool AEnemyNormal_Controller::GetIsInAttackRange()
{
	if (!targetActor)
	{
		return false;
	}
	return enemyPawn->GetDistanceTo(targetActor) <= attackRange;
}

void AEnemyNormal_Controller::PerformAttack()
{
	if (targetActor && !enemyPawn->GetIsDead() && !bisRunningBack && bWasAggroed)
	{
		bIsPatrolling = false;

		enemyPawn->GetCharacterMovement()->StopMovementImmediately();

		if (targetActor)
		{
			FRotator rot = UKismetMathLibrary::FindLookAtRotation(enemyPawn->GetActorLocation(), targetActor->GetActorLocation());
			enemyPawn->SetActorRotation(rot);
		}

		currAttackMontage = enemyPawn->attackAnimMontages[currAttackIndex];

		animInst->Montage_Play(currAttackMontage);

		GetWorldTimerManager().SetTimer(timerHandle_AnimPlayOver, this, &AEnemyNormal_Controller::OnAnimPlayOver, currAttackMontage->SequenceLength, false);
	}
}

void AEnemyNormal_Controller::OnAnimPlayOver()
{
	currAttackMontage = nullptr;
	currAttackIndex = GetNextAnimationIndex();

	if (GetIsInAttackRange())
	{
		PerformAttack();
	}
	else
	{
		if (targetActor)
		{
			MoveToActor(targetActor);
		}
	}
}

void AEnemyNormal_Controller::OnAggroedPulled(AActor* target)
{
	if (!bWasAggroed && !bisRunningBack)
	{
		bWasAggroed = true;
		targetActor = target;
		bIsPatrolling = false;

		enemyPawn->GetCharacterMovement()->MaxWalkSpeed = aggroedWalkSpeed;
		if (GetWorldTimerManager().TimerExists(timerHandle_CalDis))
		{
			GetWorldTimerManager().ClearTimer(timerHandle_CalDis);
		}
		GetWorldTimerManager().SetTimer(timerHandle_CalDis, this, &AEnemyNormal_Controller::CalcTargetDistance, 1.0f, true);
		if (GetIsInAttackRange())
		{
			PerformAttack();
		}
		else
		{
			MoveToActor(targetActor);
		}
	}
}

void AEnemyNormal_Controller::CalcTargetDistance()
{
	if (targetActor == nullptr)
	{
		return;
	}

	if (FVector::Distance(enemyPawn->GetActorLocation(), targetActor->GetActorLocation()) > maxDistanceToFollow)
	{
		OnResetActor();
	}
}

void AEnemyNormal_Controller::OnResetActor()
{
	animInst->Montage_Stop(0.0f);
	bisRunningBack = true;
	currAttackIndex = 0;
	GetWorldTimerManager().ClearTimer(timerHandle_Patrol);
	GetWorldTimerManager().ClearTimer(timerHandle_AnimPlayOver);
	GetWorldTimerManager().ClearTimer(timerHandle_CalDis);
	targetActor = nullptr;
	bWasAggroed = false;
	MoveToLocation(enemyPawn->startLocation);
	enemyPawn->ResetHealth();
}

void AEnemyNormal_Controller::OnRespawn()
{
	bIsPatrolling = true;
	bWasAggroed = false;
	targetActor = nullptr;
	currAttackIndex = 0;
	bisRunningBack = false;
	
}
