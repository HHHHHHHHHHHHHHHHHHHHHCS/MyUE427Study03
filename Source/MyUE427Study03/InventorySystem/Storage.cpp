// Fill out your copyright notice in the Description page of Project Settings.


#include "Storage.h"

// Sets default values
AStorage::AStorage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStorage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStorage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

