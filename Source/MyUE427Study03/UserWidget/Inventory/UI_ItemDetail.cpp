// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_ItemDetail.h"

#include "MyUE427Study03/Others/StaticLibrary.h"

void UUI_ItemDetail::UpdateInfo()
{
	Text_Name->SetText(itemInfo.name);
	Text_Amount->SetText(FText::AsNumber(amount));
	Text_Category->SetText(FText::FromString(UStaticLibrary::GetEnumValueAsString<EItemCategories>("EItemCategories", itemInfo.category)));
	Text_Description->SetText(itemInfo.desc);
	Image_Icon->SetBrushFromTexture(itemInfo.icon);
	Text_TotalWeight->SetText(FText::AsNumber(amount * itemInfo.weight));
	Text_SingleWeight->SetText(FText::AsNumber(itemInfo.weight));
}
