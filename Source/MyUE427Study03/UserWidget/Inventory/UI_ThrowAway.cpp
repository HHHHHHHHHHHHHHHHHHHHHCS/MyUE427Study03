// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_ThrowAway.h"

#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "MyUE427Study03/InventorySystem/ItemBase.h"

#define LOCTEXT_NAMESPACE "Throw"

void UUI_ThrowAway::UpdateInfo(int index)
{
	if (inventoryRef->IsSlotEmpty(currentIndex))
	{
		return;
	}

	AItemBase* item = inventoryRef->GetItemByIndex(index);

	currentIndex = index;
	itemInfo = item->itemInfo;
	maxAmount = inventoryRef->GetAmountAtIndex(index);
	throwCount = 1;
	Image_ItemIcon->SetBrushFromTexture(itemInfo.icon);
	Text_Name->SetText(FText::Format(LOCTEXT("Throw", "{0} x{1}")
	                                 , itemInfo.name, maxAmount));
	EText_Count->SetText(FText::AsNumber(throwCount));
}

#undef LOCTEXT_NAMESPACE
