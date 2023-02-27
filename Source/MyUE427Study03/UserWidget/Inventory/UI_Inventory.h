// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_InventorySlot.h"
#include "Blueprint/UserWidget.h"
#include "UI_Inventory.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_Inventory : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(Meta=(BindWidget))
	class UWrapBox* WBOX_Inventory;

	UPROPERTY(Meta=(BindWidget))
	class UButton* Button_Close;

public:
	TArray<UUI_InventorySlot*> inventorySlots;
	
	class AInventory* inventoryRef;
	
public:
	virtual void NativeConstruct() override;
	
	void GenerateSlotWidget();

	void OnCloseButtonClick();
};
