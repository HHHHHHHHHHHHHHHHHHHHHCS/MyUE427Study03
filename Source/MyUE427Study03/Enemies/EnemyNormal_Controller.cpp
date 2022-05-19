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
	if (GetIsInAttackRange())
	{
		PerformAttack();
		return;
	}

	if (bIsPatrolling)
	{
		float thinkTime = FMath::RandRange(1.0f, 4.0f);
		GetWorldTimerManager().SetTimer(timerHandle_patrol, this, &AEnemyNormal_Controller::DetectedPool, thinkTime, false);
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
	if (attackAnimMontages.Num() == 0)
	{
		idx = 0;
	}
	else
	{
		idx = (currAttackIndex + 1) % attackAnimMontages.Num();
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
	if (!enemyPawn->GetIsDead() && !bisRunningBack && targetActor)
	{
		bIsPatrolling = false;

		enemyPawn->GetCharacterMovement()->StopMovementImmediately();

		if (targetActor)
		{
			FRotator rot = UKismetMathLibrary::FindLookAtRotation(enemyPawn->GetActorLocation(), targetActor->GetActorLocation());
			enemyPawn->SetActorRotation(rot);
		}

		currAttackMontage = attackAnimMontages[currAttackIndex];

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
