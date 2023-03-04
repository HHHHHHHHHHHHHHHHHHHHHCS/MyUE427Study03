// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Inventory.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"

void UUI_Inventory::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Close->OnClicked.AddDynamic(this, &UUI_Inventory::OnCloseButtonClick);
}

void UUI_Inventory::GenerateSlotWidget()
{
	WBOX_Inventory->ClearChildren();
	inventorySlots.Empty();
	auto* slotCls = LoadClass<UUI_InventorySlot>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_InventorySlot.UI_InventorySlot_C'"));
	for (int i = 0; i < inventoryRef->slots.Num(); i++)
	{
		UUI_InventorySlot* slotUI = CreateWidget<UUI_InventorySlot>(GetWorld(), slotCls);
		slotUI->inventoryRef = inventoryRef;
		slotUI->slotIndex = i;
		slotUI->UpdateSlot();
		WBOX_Inventory->AddChild(slotUI);
		inventorySlots.Add(slotUI);
	}
}

void UUI_Inventory::OnCloseButtonClick()
{
	if (bInventoryShow)
	{
		SetVisibility(ESlateVisibility::Hidden);
		bInventoryShow = false;
	}
}

void UUI_Inventory::ToggleVisibility()
{
	if (bInventoryShow)
	{
		SetVisibility(ESlateVisibility::Hidden);
		bInventoryShow = false;
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
		bInventoryShow = true;
	}
}

FReply UUI_Inventory::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		dragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::RightMouseButton).NativeReply;
	}

	return FReply::Handled();
}

void UUI_Inventory::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragDropOperation* dragOp = UWidgetBlueprintLibrary::CreateDragDropOperation(inventoryDragDropOperationCls);
	dragOp->Pivot = EDragPivot::MouseDown;

	dragOp->DefaultDragVisual = this;
	OutOperation = dragOp;
	UInventoryDragDropOperation* obj = Cast<UInventoryDragDropOperation>(dragOp);
	if (obj)
	{
		obj->dragWidget = this;
		obj->mouseOffset = dragOffset;
	}
	this->RemoveFromParent();
}
