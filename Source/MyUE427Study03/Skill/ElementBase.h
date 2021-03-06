// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillElementInfo.h"
#include "ElementBase.generated.h"

UCLASS()
class MYUE427STUDY03_API AElementBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AElementBase();

	UPROPERTY(EditAnywhere, Category="ElementInfo")
	FSkillElementInfo skillElementInfo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
