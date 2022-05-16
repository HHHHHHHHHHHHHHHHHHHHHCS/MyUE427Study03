// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyNormal_Controller.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API AEnemyNormal_Controller : public AAIController
{
	GENERATED_BODY()
public:
	class UNavigationSystemV1* navSys;

	class AEnemyNormal* enemyPawn;

protected:
	FTimerHandle timerHandle_patrol;

	bool bIsPatrolling = true;

public:
	AEnemyNormal_Controller();

	virtual void OnPossess(APawn* InPawn) override;

	void Patrol();

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void DetectedPool();
};
