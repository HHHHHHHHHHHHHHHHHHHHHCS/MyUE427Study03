// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SellItem.h"


#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "MyUE427Study03/InventorySystem/ItemBase.h"

#define LOCTEXT_NAMESPACE "Sell"

void UUI_SellItem::NativeConstruct()
{
	Super::NativeConstruct();
	EText_Count->OnTextChanged.AddDynamic(this, &UUI_SellItem::ETextCountChange);

	Button_Minus->OnClicked.AddDynamic(this, &UUI_SellItem::OnButtonMinusClicked);
	Button_Minus->OnPressed.AddDynamic(this, &UUI_SellItem::OnMinusButtonPressed);
	Button_Minus->OnReleased.AddDynamic(this, &UUI_SellItem::OnMinusButtonReleased);

	Button_Plus->OnClicked.AddDynamic(this, &UUI_SellItem::OnButtonPlusClicked);
	Button_Plus->OnPressed.AddDynamic(this, &UUI_SellItem::OnButtonPlusClicked);
	Button_Plus->OnReleased.AddDynamic(this, &UUI_SellItem::OnButtonPlusClicked);

	Button_Confirm->OnClicked.AddDynamic(this, &UUI_SellItem::OnConfirmButtonClicked);
	Button_Cancel->OnClicked.AddDynamic(this, &UUI_SellItem::OnCancelButtonClicked);
}

void UUI_SellItem::UpdateInfo(int index)
{
	if (inventoryRef->IsSlotEmpty(currentIndex))
	{
		return;
	}

	AItemBase* item = inventoryRef->GetItemByIndex(index);

	currentIndex = index;
	itemInfo = item->itemInfo;
	maxAmount = inventoryRef->GetAmountAtIndex(index);
	sellCount = 1;
	Image_ItemIcon->SetBrushFromTexture(itemInfo.icon);
	Text_Name->SetText(FText::Format(LOCTEXT("Sell", "{0} x{1}")
	                                 , itemInfo.name, maxAmount));
	EText_Count->SetText(FText::AsNumber(sellCount));
	UpdatePrice();
}

void UUI_SellItem::IncreaseCount()
{
	sellCount = FMath::Clamp(sellCount + 1, 1, maxAmount);
	EText_Count->SetText(FText::AsNumber(sellCount));
	UpdatePrice();
}

void UUI_SellItem::DecreaseCount()
{
	sellCount = FMath::Clamp(sellCount - 1, 1, maxAmount);
	EText_Count->SetText(FText::AsNumber(sellCount));
	UpdatePrice();
}

void UUI_SellItem::ETextCountChange(const FText& Text)
{
	int count = FCString::Atoi(*Text.ToString());
	sellCount = FMath::Clamp(count, 1, maxAmount);
	EText_Count->SetText(FText::AsNumber(sellCount));
}

void UUI_SellItem::OnButtonMinusClicked()
{
	clickCount++;
	GetWorld()->GetTimerManager().SetTimer(
		timerHandle_CountToZero, this,
		&UUI_SellItem::SetClickCountToZero, 0.15f, false);
	if (clickCount > 1)
	{
		clickCount = 0;
		sellCount = 1;
		EText_Count->SetText(FText::AsNumber(sellCount));
		UpdatePrice();
	}
	else
	{
		this->DecreaseCount();
	}
}

void UUI_SellItem::OnButtonPlusClicked()
{
	clickCount++;
	GetWorld()->GetTimerManager().SetTimer(
		timerHandle_CountToZero, this,
		&UUI_SellItem::SetClickCountToZero, 0.15f, false);
	if (clickCount > 1)
	{
		clickCount = 0;
		sellCount = maxAmount;
		EText_Count->SetText(FText::AsNumber(sellCount));
		UpdatePrice();
	}
	else
	{
		this->IncreaseCount();
	}
}

void UUI_SellItem::OnMinusButtonPressed()
{
	GetWorld()->GetTimerManager().SetTimer(timerHandle_Decrease, this, &UUI_SellItem::DecreaseCount,
	                                       0.1f, true, 0.5f);
}

void UUI_SellItem::OnPlusButtonPressed()
{
	GetWorld()->GetTimerManager().SetTimer(timerHandle_Increase, this, &UUI_SellItem::IncreaseCount,
	                                       0.1f, true, 0.5f);
}

void UUI_SellItem::OnMinusButtonReleased()
{
	GetWorld()->GetTimerManager().ClearTimer(timerHandle_Decrease);
}

void UUI_SellItem::OnPlusButtonReleased()
{
	GetWorld()->GetTimerManager().ClearTimer(timerHandle_Increase);
}

void UUI_SellItem::OnConfirmButtonClicked()
{
	if (inventoryRef->RemoveItemAtIndex(currentIndex, sellCount))
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		inventoryRef->playerChar->mainUI->inventoryWidget->WBOX_Inventory->SetIsEnabled(true);
	}
}

void UUI_SellItem::OnCancelButtonClicked()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	inventoryRef->playerChar->mainUI->inventoryWidget->WBOX_Inventory->SetIsEnabled(true);
}

void UUI_SellItem::SetClickCountToZero()
{
	clickCount = 0;
	GetWorld()->GetTimerManager().ClearTimer(timerHandle_CountToZero);
}

void UUI_SellItem::UpdatePrice()
{
	Text_Price->SetText(FText::AsNumber(itemInfo.price * sellCount));
}


#undef LOCTEXT_NAMESPACE
