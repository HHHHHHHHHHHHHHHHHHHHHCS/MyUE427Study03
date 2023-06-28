// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_RecipeEntry.h"

#include "UI_CraftMenu.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "MyUE427Study03/InventorySystem/ItemBase.h"

#define LOCTEXT_NAMESPACE "UUI_RecipeEntry"

void UUI_RecipeEntry::Update()
{
	auto defaultObj = item->GetDefaultObject<AItemBase>();
	Image_Icon->SetBrushFromTexture(defaultObj->itemInfo.icon);
	TArray<int> itemSlots;
	currentAmount = craftMenu->inventory->GetTotalAmountOfItem(item, itemSlots);
	Text_Name->SetText(FText::Format(LOCTEXT("UUI_RecipeEntry", "{0}({1}/{2})")
	                                 , defaultObj->itemInfo.name
	                                 , FText::AsNumber(currentAmount)
	                                 , FText::AsNumber(requiredAmount)));

	if(currentAmount>=requiredAmount)
	{
		Text_Name->SetColorAndOpacity(FLinearColor::White);
	}
	else
	{
		Text_Name->SetColorAndOpacity(FLinearColor::Red);
	}
	

}

#undef LOCTEXT_NAMESPACE
