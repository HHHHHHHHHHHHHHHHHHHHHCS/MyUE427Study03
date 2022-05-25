// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementBase.h"

//元素比如金木水火土

// Sets default values
AElementBase::AElementBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElementBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
