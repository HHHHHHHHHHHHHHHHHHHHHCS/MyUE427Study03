// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyNormal.h"

#include "EnemyNormal_Controller.h"

// Sets default values
AEnemyNormal::AEnemyNormal()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AEnemyNormal_Controller::StaticClass();
}

// Called when the game starts or when spawned
void AEnemyNormal::BeginPlay()
{
	Super::BeginPlay();
	myController = Cast<AEnemyNormal_Controller>(GetController());
	myController->Patrol();
}

// Called every frame
void AEnemyNormal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyNormal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
