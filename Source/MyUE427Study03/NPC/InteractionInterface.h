// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InteractionInterface.generated.h"

/**
 * 
 */
UINTERFACE()
class MYUE427STUDY03_API UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class IInteractionInterface
{
	GENERATED_BODY()

public:
	virtual void OnEnterPlayerRadius(class ACharacterBase* character) = 0;

	virtual void OnLeavePlayerRadius(class ACharacterBase* character) = 0;

	virtual void OnInteractWith(class ACharacterBase* character) = 0;
};
