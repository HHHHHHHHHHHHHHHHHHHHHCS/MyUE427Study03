// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_InventorySlot.h"

#include "Components/Button.h"
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
