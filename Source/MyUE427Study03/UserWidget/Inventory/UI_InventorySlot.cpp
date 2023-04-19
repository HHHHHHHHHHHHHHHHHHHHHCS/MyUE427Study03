// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_InventorySlot.h"

#include "UI_DragItem.h"
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
	}
}

void UUI_InventorySlot::OnButtonSlotClicked()
{
	inventoryRef->UpdateActionMenuPosition(this);
}

FReply UUI_InventorySlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//UE Button下面有Image 可能双击会触发不动
	//需要把Image 放到border下就好了
	Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) && itemInfo.canUsed)
	{
		inventoryRef->UseItemAtIndex(slotIndex);
		return FReply::Handled();
	}
	else
	{
		return FReply::Handled();
	}
}

FReply UUI_InventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::RightMouseButton).NativeReply;
	}
	else
	{
		return FReply::Handled();
	}
}

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
	else
	{
		if (Cast<UUI_ItemDragDropOperation>(InOperation))
		{
			UE_LOG(LogTemp,Log,TEXT("11111"));
			bDraggedOver = true;
			Border_Base->SetBrushColor(FLinearColor(1.0f, 0.82f, 0.0f, 0.5f));
			return true;
		}
		else
		{
			return false;
		}
	}
}
