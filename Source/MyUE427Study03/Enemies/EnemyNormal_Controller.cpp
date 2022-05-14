// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyNormal_Controller.h"

#include "EnemyNormal.h"

void AEnemyNormal_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	enemyPawn = Cast<AEnemyNormal>(InPawn);
}
