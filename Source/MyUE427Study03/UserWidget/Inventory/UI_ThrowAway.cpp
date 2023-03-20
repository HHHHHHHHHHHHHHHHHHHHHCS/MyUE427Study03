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

	Button_Minus->OnClicked.AddDynamic(this, &UUI_ThrowAway::OnButtonMinusClicked);
	Button_Minus->OnPressed.AddDynamic(this, &UUI_ThrowAway::OnMinusButtonPressed);
	Button_Minus->OnReleased.AddDynamic(this, &UUI_ThrowAway::OnMinusButtonReleased);

	Button_Plus->OnClicked.AddDynamic(this, &UUI_ThrowAway::OnButtonPlusClicked);
	Button_Plus->OnPressed.AddDynamic(this, &UUI_ThrowAway::OnButtonPlusClicked);
	Button_Plus->OnReleased.AddDynamic(this, &UUI_ThrowAway::OnButtonPlusClicked);
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
	clickCount++;
	GetWorld()->GetTimerManager().SetTimer(
		timerHandle_CountToZero, this,
		&UUI_ThrowAway::SetClickCountToZero, 0.3f, false);
	if (clickCount > 1)
	{
		clickCount = 0;
		throwCount = 1;
		EText_Count->SetText(FText::AsNumber(throwCount));
	}
	else
	{
		this->DecreaseCount();
	}
}

void UUI_ThrowAway::OnButtonPlusClicked()
{
	clickCount++;
	GetWorld()->GetTimerManager().SetTimer(
		timerHandle_CountToZero, this,
		&UUI_ThrowAway::SetClickCountToZero, 0.3f, false);
	if (clickCount > 1)
	{
		clickCount = 0;
		throwCount = maxAmount;
		EText_Count->SetText(FText::AsNumber(throwCount));
	}
	else
	{
		this->IncreaseCount();
	}
}

void UUI_ThrowAway::OnMinusButtonPressed()
{
	GetWorld()->GetTimerManager().SetTimer(timerHandle_Decrease, this, &UUI_ThrowAway::DecreaseCount,
	                                       1, true, 0.0f);
}

void UUI_ThrowAway::OnPlusButtonPressed()
{
	GetWorld()->GetTimerManager().SetTimer(timerHandle_Increase, this, &UUI_ThrowAway::IncreaseCount,
	                                       1, true, 0.0f);
}

void UUI_ThrowAway::OnMinusButtonReleased()
{
	GetWorld()->GetTimerManager().ClearTimer(timerHandle_Decrease);
}

void UUI_ThrowAway::OnPlusButtonReleased()
{
	GetWorld()->GetTimerManager().ClearTimer(timerHandle_Increase);
}

void UUI_ThrowAway::SetClickCountToZero()
{
	clickCount = 0;
	GetWorld()->GetTimerManager().ClearTimer(timerHandle_CountToZero);
}


#undef LOCTEXT_NAMESPACE
