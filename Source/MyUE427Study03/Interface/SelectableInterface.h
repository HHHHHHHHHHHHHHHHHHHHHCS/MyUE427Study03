// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectableInterface.generated.h"

UINTERFACE()
class USelectableInterface : public UInterface
{
	GENERATED_BODY()
};

class ISelectableInterface
{
	GENERATED_BODY()

public:
	//选中
	virtual void OnSelected(class ACharacterBase* character) = 0;
	//离开选中
	virtual void OnSelectionEnd(class ACharacterBase* character) = 0;
};
