// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyNormal_Controller.h"

#include "EnemyNormal.h"
#include "NavigationSystem.h"

AEnemyNormal_Controller::AEnemyNormal_Controller()
{
	navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
}

void AEnemyNormal_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	enemyPawn = Cast<AEnemyNormal>(InPawn);
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
	if (attackAnimMontages.Num() == 0)
	{
		currAttackIndex = 0;
	}
	else
	{
		currAttackIndex = (currAttackIndex + 1) % attackAnimMontages.Num();
	}

	return currAttackIndex;
}

bool AEnemyNormal_Controller::GetIsInAttackRange()
{
	if (!targetActor)
	{
		return false;
	}
	return enemyPawn->GetDistanceTo(targetActor) <= attackRange;
}
