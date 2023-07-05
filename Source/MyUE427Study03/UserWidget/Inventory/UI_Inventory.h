// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryDragDropOperation.h"
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

	UPROPERTY(Meta=(BindWidget))
	class UComboBoxString* CBox_SortCategory;

	UPROPERTY(Meta=(BindWidget))
	class UButton* Button_Sort;


	UPROPERTY(Meta=(BindWidget))
	class UTextBlock* Text_CurrentWeight;

	UPROPERTY(Meta=(BindWidget))
	class UTextBlock* Text_TotalWeight;

	UPROPERTY(Meta=(BindWidget))
	class UTextBlock* Text_Coin;

public:
	TArray<UUI_InventorySlot*> inventorySlots;

	class AInventory* inventoryRef;

	bool bInventoryShow = false;

	FVector2D dragOffset;

	class UUI_InventoryActionMenu* actionMenu;

	bool isReversed = false;

protected:
	UPROPERTY(EditAnywhere, Category="DragDrop")
	TSubclassOf<UInventoryDragDropOperation> inventoryDragDropOperationCls;

public:
	virtual void NativeConstruct() override;

	void GenerateSlotWidget();

	UFUNCTION()
	void OnCloseButtonClick();

	void ToggleVisibility();

	UFUNCTION()
	void OnSortButtonClick();

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	void UpdateWeight(float currWeight, float totalWeight);

	void UpdateCoin(int amount);
};
