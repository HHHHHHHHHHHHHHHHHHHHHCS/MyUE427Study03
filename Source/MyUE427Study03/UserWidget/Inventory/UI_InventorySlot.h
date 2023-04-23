// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUE427Study03/InventorySystem/InventoryStruct.h"
#include "UI_InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_InventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	class UButton* Button_Slot;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_Amount;

	UPROPERTY(meta=(BindWidget))
	class UImage* Image_Icon;

	UPROPERTY(meta=(BindWidget))
	class UBorder* Border_Base;

	UPROPERTY(EditAnywhere, Category="Drag")
	TSubclassOf<class UDragDropOperation> itemDragDropOp;

public:
	int slotIndex;
	int amount;
	class AInventory* inventoryRef;
	FItemInfo itemInfo;
	bool bDraggedOver;

public:
	virtual void NativeConstruct() override;

	void UpdateSlot();

	UFUNCTION()
	void OnButtonSlotClicked();

	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
