// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestPropBase.h"

// Sets default values
AQuestPropBase::AQuestPropBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	SetRootComponent(staticMesh);
	interactionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	interactionWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AQuestPropBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AQuestPropBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
