// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class MYUE427STUDY03_API AItemBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemBase();

public:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* sphereCollisionComp;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* interactionUI;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* staticMeshComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
