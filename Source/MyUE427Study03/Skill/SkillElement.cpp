// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillElement.h"

//元素比如金木水火土

// Sets default values
ASkillElement::ASkillElement()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkillElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkillElement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

