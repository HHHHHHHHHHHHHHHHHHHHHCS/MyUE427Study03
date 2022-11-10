// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalActor.generated.h"

UCLASS()
class MYUE427STUDY03_API AGoalActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* defaultRootComp;

	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* minimapIcon;

	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* questAreaIcon;

public:
	// Sets default values for this actor's properties
	AGoalActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
