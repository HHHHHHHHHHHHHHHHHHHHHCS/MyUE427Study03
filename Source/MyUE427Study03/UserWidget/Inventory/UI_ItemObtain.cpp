// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_ItemObtain.h"

#include "MyUE427Study03/InventorySystem/ItemBase.h"

void UUI_ItemObtain::OnInit(TSubclassOf<AItemBase> itemCls, int amount)
{
	AItemBase* item = itemCls.GetDefaultObject();
	Text_Name->SetText(item->itemInfo.name);
	Text_Amount->SetText(FText::AsNumber(amount));
	Image_Icon->SetBrushFromTexture(item->itemInfo.icon);
	FLinearColor tempColor;
	switch (item->itemInfo.category)
	{
	case EItemCategories::Consume:
		tempColor = FLinearColor::White;
		break;
	case EItemCategories::Equipment:
		tempColor = FLinearColor::Red;
		break;
	case EItemCategories::QuestItem:
		tempColor = FLinearColor::Yellow;
		break;
	case EItemCategories::Readable:
		tempColor = FLinearColor::Gray;
		break;
	}
	Text_Name->SetColorAndOpacity(tempColor);
	Text_X->SetColorAndOpacity(tempColor);
	Text_Amount->SetColorAndOpacity(tempColor);
	Text_Obtain->SetColorAndOpacity(tempColor);
}
