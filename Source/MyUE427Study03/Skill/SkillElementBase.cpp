// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillElementBase.h"

//元素比如金木水火土

// Sets default values
ASkillElementBase::ASkillElementBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkillElementBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASkillElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
