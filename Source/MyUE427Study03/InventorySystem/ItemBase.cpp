// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

// Sets default values
AItemBase::AItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComp"));
	SetRootComponent(sphereCollisionComp);
	staticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	staticMeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
