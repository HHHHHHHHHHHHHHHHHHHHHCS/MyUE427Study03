// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MinimapCamera.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API AMinimapCamera : public ASceneCapture2D
{
	GENERATED_BODY()

public:
	float offsetZ;

	ACharacterBase* mainPlayer;

public:
	AMinimapCamera();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void OutsideTick();
};
