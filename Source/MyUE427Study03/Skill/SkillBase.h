// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillInfo.h"
#include "GameFramework/Actor.h"
#include "SkillBase.generated.h"


UCLASS()
class MYUE427STUDY03_API ASkillBase : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Skill Info")
	FSkillInfo skillInfo;

	int currentStageIndex;

public:
	// Sets default values for this actor's properties
	ASkillBase();

	FORCEINLINE FSkillStage GetCurrentStage()
	
	{
		return skillInfo.stages[currentStageIndex];
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
