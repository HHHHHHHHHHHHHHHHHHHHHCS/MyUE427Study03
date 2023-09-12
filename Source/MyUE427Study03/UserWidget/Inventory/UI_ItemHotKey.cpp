// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_ItemHotKey.h"

#include "UI_InventorySlot.h"
#include "UI_ItemDragDropOperation.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "MyUE427Study03/InventorySystem/ItemBase.h"

void UUI_ItemHotKey::UpdateInfo()
{
	if (isEmpty)
	{
		Image_Icon->SetVisibility(ESlateVisibility::Hidden);
		HBOX_Amount->SetVisibility(ESlateVisibility::Hidden);
		isDragOver = false;
		Border_Bg->SetBrushColor(defaultTint);
	}
	else
	{
		AItemBase* item = inventory->GetItemByIndex(inventoryIndex);
		if (item == nullptr)
		{
			Image_Icon->SetVisibility(ESlateVisibility::Hidden);
			HBOX_Amount->SetVisibility(ESlateVisibility::Hidden);
			isDragOver = false;
			Border_Bg->SetBrushColor(defaultTint);
		}
		else
		{
			Image_Icon->SetBrushFromTexture(item->itemInfo.icon);
			Image_Icon->SetVisibility(ESlateVisibility::Visible);
			Text_Amount->SetText(FText::AsNumber(item->amount));
			HBOX_Amount->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

bool UUI_ItemHotKey::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	if (isDragOver)
	{
		return true;
	}

	if (Cast<UUI_ItemDragDropOperation>(InOperation))
	{
		isDragOver = true;
		Border_Bg->SetBrushColor(dragOverTint);
		return true;
	}
	return false;
}

void UUI_ItemHotKey::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	if (isDragOver)
	{
		if (Cast<UUI_ItemDragDropOperation>(InOperation))
		{
			Border_Bg->SetBrushColor(defaultTint);
			isDragOver = false;
		}
	}
}

bool UUI_ItemHotKey::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	auto dragOp = Cast<UUI_ItemDragDropOperation>(InOperation);
	if (dragOp)
	{
		auto slot = dragOp->slot;
		inventoryIndex = slot->slotIndex;
		isEmpty = false;
		UpdateInfo();
		isDragOver = false;
		Border_Bg->SetBrushColor(defaultTint);
		return true;
	}
	return false;
}

FReply UUI_ItemHotKey::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) && !isEmpty)
	{
		isEmpty = true;
		UpdateInfo();
	}

	return FReply::Handled();
}
