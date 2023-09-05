// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_StorageSlot.h"
#include "Blueprint/UserWidget.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "UI_Storage.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_Storage : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Meta=(BindWidget))
	class UWrapBox* WBOX_Storage;

	UPROPERTY(Meta=(BindWidget))
	class UButton* Button_Close;


public:
	TArray<UUI_StorageSlot*> storageSlotArray;

	class AStorage* storageRef;

	class AInventory* inventoryRef;

public:
	virtual void NativeConstruct() override;

	void GenerateSlot(AStorage* storage, AInventory* Inventory);
	
	UFUNCTION()
	void OnCloseButtonClick();

	UFUNCTION()
	void OnSlotClicked(int index);
};
