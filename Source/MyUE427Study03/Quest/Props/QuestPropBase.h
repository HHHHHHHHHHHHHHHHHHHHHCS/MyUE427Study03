// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "QuestPropBase.generated.h"

UCLASS()
class MYUE427STUDY03_API AQuestPropBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQuestPropBase();

public:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* staticMesh;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* interactionWidget;

	UPROPERTY(EditAnywhere, Category="Quest")
	FText name;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
