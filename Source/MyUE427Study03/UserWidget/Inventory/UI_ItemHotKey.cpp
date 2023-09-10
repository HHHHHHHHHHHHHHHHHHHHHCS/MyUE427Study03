// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_ItemHotKey.h"

#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "MyUE427Study03/InventorySystem/ItemBase.h"

void UUI_ItemHotKey::UpdateInfo()
{
	if(isEmpty)
	{
		Image_Icon->SetVisibility(ESlateVisibility::Hidden);
		Text_Amount->SetVisibility(ESlateVisibility::Hidden);
		isDragOver = false;
		Border_Bg->SetBrushColor(defaultTint);
	}
	else
	{
		AItemBase* item = inventory->GetItemByIndex(inventoryIndex);
		if(item == nullptr)
		{
			Image_Icon->SetVisibility(ESlateVisibility::Hidden);
			Text_Amount->SetVisibility(ESlateVisibility::Hidden);
			isDragOver = false;
			Border_Bg->SetBrushColor(defaultTint);
		}
		else
		{
			Image_Icon->SetBrushFromTexture(item->itemInfo.icon);
			Image_Icon->SetVisibility(ESlateVisibility::Visible);
			Text_Amount->SetText(FText::AsNumber(item->amount));
			Text_Amount->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
