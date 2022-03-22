// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CursorDecal.generated.h"

UCLASS()
class MYUE427STUDY03_API ACursorDecal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACursorDecal();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cursor")
	USceneComponent* sceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cursor")
	UDecalComponent* cursorToWorld;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cursor")
	UBoxComponent* boxComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
