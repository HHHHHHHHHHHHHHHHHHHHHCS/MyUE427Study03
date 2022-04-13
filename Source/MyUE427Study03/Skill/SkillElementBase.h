// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillElementInfo.h"
#include "SkillElementBase.generated.h"

UCLASS()
class MYUE427STUDY03_API ASkillElementBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASkillElementBase();

	UPROPERTY(EditAnywhere, Category="ElementInfo")
	FSkillElementInfo skillElementInfo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
