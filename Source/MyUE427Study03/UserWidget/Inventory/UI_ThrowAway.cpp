// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_ThrowAway.h"

#include "Kismet/KismetStringLibrary.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "MyUE427Study03/InventorySystem/ItemBase.h"

#define LOCTEXT_NAMESPACE "Throw"


void UUI_ThrowAway::NativeConstruct()
{
	Super::NativeConstruct();
	EText_Count->OnTextChanged.AddDynamic(this, &UUI_ThrowAway::ETextCountChange);
}

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

void UUI_ThrowAway::IncreaseCount()
{
	throwCount = FMath::Clamp(throwCount + 1, 1, maxAmount);
	EText_Count->SetText(FText::AsNumber(throwCount));
}

void UUI_ThrowAway::DecreaseCount()
{
	throwCount = FMath::Clamp(throwCount - 1, 1, maxAmount);
	EText_Count->SetText(FText::AsNumber(throwCount));
}

void UUI_ThrowAway::ETextCountChange(const FText& Text)
{
	int count = FCString::Atoi(*Text.ToString());
	throwCount = FMath::Clamp(count, 1, maxAmount);
	EText_Count->SetText(FText::AsNumber(throwCount));
}

void UUI_ThrowAway::OnButtonMinusClicked()
{
	this->DecreaseCount();
}

void UUI_ThrowAway::OnButtonPlusClicked()
{
	this->IncreaseCount();
}

#undef LOCTEXT_NAMESPACE
