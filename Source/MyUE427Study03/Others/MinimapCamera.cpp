// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimapCamera.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"

AMinimapCamera::AMinimapCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCaptureComponent2D()->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	offsetZ = 1200.0f;
	FVector location = GetActorLocation();
	location.Z = offsetZ;
	SetActorLocation(location);
}

void AMinimapCamera::BeginPlay()
{
	Super::BeginPlay();
	mainPlayer = Cast<ACharacterBase>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AMinimapCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	OutsideTick();
}

void AMinimapCamera::OutsideTick()
{
	FVector targetLocation = mainPlayer->GetActorLocation();
	targetLocation.Z = mainPlayer->GetActorLocation().Z + offsetZ;
	SetActorLocation(targetLocation);
}
