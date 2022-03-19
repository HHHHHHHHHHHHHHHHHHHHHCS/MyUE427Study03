// Fill out your copyright notice in the Description page of Project Settings.


#include "CursorDecal.h"

#include "Components/DecalComponent.h"

// Sets default values
ACursorDecal::ACursorDecal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(sceneRoot);

	cursorToWorld = CreateDefaultSubobject<UDecalComponent>(TEXT("CursorDecal"));
	cursorToWorld->SetupAttachment(sceneRoot);
	cursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	cursorToWorld->SetRelativeRotation(FRotator(90, 0, 0));

	const auto materialFinder = ConstructorHelpers::FObjectFinder<UMaterial>(
		TEXT("Material'/Game/Textures/Others/M_Cursor_Decal.M_Cursor_Decal'"));

	if (materialFinder.Succeeded())
	{
		cursorToWorld->SetDecalMaterial(materialFinder.Object);
	}
}

// Called when the game starts or when spawned
void ACursorDecal::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACursorDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
