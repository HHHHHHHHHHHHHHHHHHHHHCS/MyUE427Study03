// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyUE427Study03/InventorySystem/InventoryStruct.h"
#include "UI_InventorySlot.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_InventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta=(BindWidget))
	UButton* Button_Slot;

	UPROPERTY(Meta=(BindWidget))
	UTextBlock* Text_Amount;

	UPROPERTY(Meta=(BindWidget))
	UImage* Image_Icon;

public:
	int slotIndex;
	int amount;
	class AInventory* inventoryRef;
	FItemInfo itemInfo;

public:
	void UpdateSlot();
};
