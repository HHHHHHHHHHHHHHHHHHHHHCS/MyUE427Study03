// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_StorageSlot.h"

#include "StorageSlotDragDropOperation.h"
#include "UI_DragItem.h"
#include "UI_InventoryActionMenu.h"
#include "UI_ItemDetail.h"
#include "UI_ItemDragDropOperation.h"
#include "UI_Storage.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/InventorySystem/Storage.h"

void UUI_StorageSlot::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Slot->OnClicked.AddDynamic(this, &UUI_StorageSlot::OnButtonSlotClicked);
}

void UUI_StorageSlot::UpdateSlot()
{
	if (storageRef->IsSlotEmpty(slotIndex))
	{
		Button_Slot->SetIsEnabled(false);
		Image_Icon->SetVisibility(ESlateVisibility::Hidden);
		Text_Amount->SetVisibility(ESlateVisibility::Hidden);
		Button_Slot->SetToolTip(nullptr);
	}
	else
	{
		Button_Slot->SetIsEnabled(true);
		AItemBase* item = storageRef->GetItemByIndex(slotIndex);
		itemInfo = item->itemInfo;
		amount = storageRef->GetAmountAtIndex(slotIndex);
		Image_Icon->SetBrushFromTexture(itemInfo.icon);
		Image_Icon->SetVisibility(ESlateVisibility::HitTestInvisible);
		if (itemInfo.canStacked)
		{
			Text_Amount->SetText(FText::AsNumber(amount));
			Text_Amount->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
		else
		{
			Text_Amount->SetVisibility(ESlateVisibility::Hidden);
		}

		if (!itemDetail)
		{
			auto cls = LoadClass<UUI_ItemDetail>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_ItemDetail.UI_ItemDetail_C'"));
			itemDetail = CreateWidget<UUI_ItemDetail>(GetWorld(), cls);
		}
		itemDetail->itemInfo = itemInfo;
		itemDetail->amount = amount;
		Button_Slot->SetToolTip(itemDetail);
		itemDetail->UpdateInfo();
	}
}

void UUI_StorageSlot::OnButtonSlotClicked()
{
	storageRef->GetStorageWidget()->OnSlotClicked(slotIndex);
}

FReply UUI_StorageSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::RightMouseButton).NativeReply;
	}
	return FReply::Handled();
}


void UUI_StorageSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (!storageRef->IsSlotEmpty(slotIndex))
	{
		auto cls = LoadClass<UUI_DragItem>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_DragItem.UI_DragItem_C'"));
		UUI_DragItem* itemDrag = CreateWidget<UUI_DragItem>(GetWorld(), cls);
		itemDrag->OnInit(amount, storageRef->GetItemByIndex(slotIndex)->itemInfo.icon);

		UDragDropOperation* tempOp = UWidgetBlueprintLibrary::CreateDragDropOperation(itemDragDropOp);
		tempOp->DefaultDragVisual = itemDrag;
		OutOperation = tempOp;

		UStorageSlotDragDropOperation* dragDropOp = Cast<UStorageSlotDragDropOperation>(OutOperation);

		if (dragDropOp)
		{
			dragDropOp->slot = this;
		}
	}
}

bool UUI_StorageSlot::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
	if (bDraggedOver)
	{
		return true;
	}

	auto itemDragOp = Cast<UUI_ItemDragDropOperation>(InOperation);

	if (itemDragOp)
	{
		bDraggedOver = true;
		Border_Base->SetBrushColor(FLinearColor(1.0f, 0.82f, 0.0f, 0.5f));
		return true;
	}

	auto storageDragOp = Cast<UStorageSlotDragDropOperation>(InOperation);
	if (storageDragOp && storageDragOp->slot != this)
	{
		bDraggedOver = true;
		Border_Base->SetBrushColor(FLinearColor(1.0f, 0.82f, 0.0f, 0.5f));
		return true;
	}
	return false;
}

void UUI_StorageSlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	if (bDraggedOver)
	{
		auto itemDragOp = Cast<UUI_ItemDragDropOperation>(InOperation);
		auto storageDragOp = Cast<UStorageSlotDragDropOperation>(InOperation);

		if (itemDragOp || storageDragOp)
		{
			CancelOverColor();
		}
	}
}

bool UUI_StorageSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	auto storageDragOp = Cast<UStorageSlotDragDropOperation>(InOperation);

	if (storageDragOp)
	{
		CancelOverColor();
		if (storageRef->AddToIndex(storageDragOp->slot->slotIndex, slotIndex))
		{
			return true;
		}
		// 如果尝试添加失败  那就直接交换
		return storageRef->SwapSlot(storageDragOp->slot->slotIndex, slotIndex);
	}

	auto itemDragOp = Cast<UUI_ItemDragDropOperation>(InOperation);

	if (itemDragOp)
	{
		CancelOverColor();
		return storageRef->MoveFromInventoryToStorageByIndex(itemDragOp->slot->inventoryRef,
		                                                     itemDragOp->slot->slotIndex, slotIndex);
	}


	return false;
}

void UUI_StorageSlot::CancelOverColor()
{
	Border_Base->SetBrushColor(FLinearColor(1, 1, 1, 0));
	bDraggedOver = false;
}
