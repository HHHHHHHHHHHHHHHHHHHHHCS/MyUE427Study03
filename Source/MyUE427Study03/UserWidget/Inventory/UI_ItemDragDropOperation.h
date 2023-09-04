// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "UI_ItemDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_ItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	class UUI_InventorySlot* slot;
	bool isShiftDown;
};
