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
	class AEnemyNormal* enemyPawn;


public:
	virtual void OnPossess(APawn* InPawn) override;
};
