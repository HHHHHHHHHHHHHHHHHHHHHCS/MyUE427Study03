// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_InventorySlot.h"

#include "UI_DragItem.h"
#include "UI_InventoryActionMenu.h"
#include "UI_ItemDetail.h"
#include "UI_ItemDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "MyUE427Study03/InventorySystem/ItemBase.h"

void UUI_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Slot->OnClicked.AddDynamic(this, &UUI_InventorySlot::OnButtonSlotClicked);
}

void UUI_InventorySlot::UpdateSlot()
{
	if (inventoryRef->IsSlotEmpty(slotIndex))
	{
		Button_Slot->SetIsEnabled(false);
		Image_Icon->SetVisibility(ESlateVisibility::Hidden);
		Text_Amount->SetVisibility(ESlateVisibility::Hidden);
		Button_Slot->SetToolTip(nullptr);
	}
	else
	{
		Button_Slot->SetIsEnabled(true);
		AItemBase* item = inventoryRef->GetItemByIndex(slotIndex);
		itemInfo = item->itemInfo;
		amount = inventoryRef->GetAmountAtIndex(slotIndex);
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

void UUI_InventorySlot::SetClickCountZero()
{
	clickCount = 0;
	inventoryRef->UpdateActionMenuPosition(this);
	GetWorld()->GetTimerManager().ClearTimer(timerHandle_CountToZero);
}

void UUI_InventorySlot::OnButtonSlotClicked()
{
	clickCount++;
	GetWorld()->GetTimerManager().SetTimer(timerHandle_CountToZero, this, &UUI_InventorySlot::SetClickCountZero, 0.3f, false);
	if (clickCount >= 2)
	{
		inventoryRef->UseItemAtIndex(slotIndex);
		clickCount = 0;
		inventoryRef->playerChar->mainUI->inventoryWidget->actionMenu->SetVisibility(ESlateVisibility::Hidden);
		GetWorld()->GetTimerManager().ClearTimer(timerHandle_CountToZero);
	}
}

// FReply UUI_InventorySlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
// {
// 	//UE Button下面有Image 可能双击会触发不动
// 	//需要把Image 放到border下就好了
// 	Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
// 	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) && itemInfo.canUsed)
// 	{
// 		inventoryRef->playerChar->mainUI->inventoryWidget->actionMenu->SetVisibility(ESlateVisibility::Hidden);
// 		inventoryRef->UseItemAtIndex(slotIndex);
// 		return FReply::Handled();
// 	}
// 	else
// 	{
// 		return FReply::Handled();
// 	}
// }

FReply UUI_InventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::RightMouseButton).NativeReply;
	}
	return FReply::Handled();
}

// FReply UUI_InventorySlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
// {
// 	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
//
// 	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
// 	{
// 		if (!inventoryRef->IsSlotEmpty(slotIndex))
// 		{
// 			inventoryRef->UpdateActionMenuPosition(this);
// 		}
// 	}
// 	else if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
// 	{
// 		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::RightMouseButton).NativeReply;
// 	}
// 	return FReply::Handled();
// }

void UUI_InventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (!inventoryRef->IsSlotEmpty(slotIndex))
	{
		auto cls = LoadClass<UUI_DragItem>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_DragItem.UI_DragItem_C'"));
		UUI_DragItem* itemDrag = CreateWidget<UUI_DragItem>(GetWorld(), cls);
		itemDrag->OnInit(amount, inventoryRef->GetItemByIndex(slotIndex)->itemInfo.icon);

		UDragDropOperation* tempOp = UWidgetBlueprintLibrary::CreateDragDropOperation(itemDragDropOp);
		tempOp->DefaultDragVisual = itemDrag;
		OutOperation = tempOp;

		UUI_ItemDragDropOperation* dragDropOp = Cast<UUI_ItemDragDropOperation>(OutOperation);

		if (dragDropOp)
		{
			dragDropOp->isShiftDown = inventoryRef->playerChar->isShiftDown;
			dragDropOp->uiDragSlot = this;
		}
	}
}

bool UUI_InventorySlot::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
	if (bDraggedOver)
	{
		return true;
	}
	auto dragOp = Cast<UUI_ItemDragDropOperation>(InOperation);
	if (dragOp)
	{
		if (dragOp->uiDragSlot != this)
		{
			bDraggedOver = true;
			Border_Base->SetBrushColor(FLinearColor(1.0f, 0.82f, 0.0f, 0.5f));
		}
		return true;
	}
	return false;
}

void UUI_InventorySlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	if (bDraggedOver)
	{
		auto dragOp = Cast<UUI_ItemDragDropOperation>(InOperation);
		if (dragOp)
		{
			Border_Base->SetBrushColor(FLinearColor(1, 1, 1, 0));
			bDraggedOver = false;
		}
	}
}

bool UUI_InventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	auto dragOp = Cast<UUI_ItemDragDropOperation>(InOperation);

	if (dragOp)
	{
		auto slot = dragOp->uiDragSlot;
		if (slot != this)
		{
			bDraggedOver = false;
			Border_Base->SetBrushColor(FLinearColor(1, 1, 1, 0));
			if (inventoryRef->AddToIndex(slot->slotIndex, slotIndex))
			{
				return true;
			}
			else
			{
				if (dragOp->isShiftDown)
				{
					inventoryRef->SplitStackToIndex(slot->slotIndex, slotIndex, slot->amount / 2);
				}
				else
				{
					inventoryRef->SwapSlot(slot->slotIndex, slotIndex);
				}

				return true;
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}
