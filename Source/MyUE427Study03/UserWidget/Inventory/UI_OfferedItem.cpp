// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_OfferedItem.h"

#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "MyUE427Study03/InventorySystem/ItemBase.h"

void UUI_OfferedItem::NativeConstruct()
{
	Super::NativeConstruct();
	Slider_Amount->OnValueChanged.AddDynamic(this, &UUI_OfferedItem::OnSliderChanged);
	Button_Buy->OnClicked.AddDynamic(this, &UUI_OfferedItem::UUI_OfferedItem::OnClickButtonBuy);
}


void UUI_OfferedItem::Init(TSubclassOf<AItemBase> item, class AInventory* _inventory)
{
	inventory = _inventory;
	assignedItem = item;
	itemInfo = assignedItem->GetDefaultObject<AItemBase>()->itemInfo;
	Image_Icon->SetBrushFromTexture(itemInfo.icon);
	Text_Name->SetText(itemInfo.name);

	if (itemInfo.canStacked)
	{
		Text_Amount->SetVisibility(ESlateVisibility::Visible);
		Slider_Amount->SetVisibility(ESlateVisibility::Visible);
		currentAmount = 1;
		Text_Amount->SetText(FText::AsNumber(currentAmount));
	}
	else
	{
		Text_Amount->SetVisibility(ESlateVisibility::Hidden);
		Slider_Amount->SetVisibility(ESlateVisibility::Hidden);
		currentAmount = 1;
		Slider_Amount->SetValue(0);
	}

	UpdatePrice();
}

void UUI_OfferedItem::UpdatePrice()
{
	int needCoin = itemInfo.price * currentAmount;
	Text_Price->SetText(FText::AsNumber(needCoin));
	if (inventory->playerChar->GetCurrentCoin() >= needCoin)
	{
		Button_Buy->SetIsEnabled(true);
		Text_Price->SetColorAndOpacity(FLinearColor(1.0f, 0.48f, 0.0f, 1.0f));
	}
	else
	{
		Button_Buy->SetIsEnabled(false);
		Text_Price->SetColorAndOpacity(FLinearColor::Red);
	}
}


void UUI_OfferedItem::OnSliderChanged(float value)
{
	currentAmount = FMath::Lerp(1, maxAmount, value);
	Text_Amount->SetText(FText::AsNumber(currentAmount));
	UpdatePrice();
}

void UUI_OfferedItem::OnClickButtonBuy()
{
	int needCoin = itemInfo.price * currentAmount;
	if (inventory->playerChar->GetCurrentCoin() >= needCoin)
	{
		int remainedCount = inventory->AddItem(assignedItem, currentAmount);

		if (remainedCount <= 0)
		{
			inventory->playerChar->DecreaseCoin(needCoin);
		}
		else
		{
			inventory->playerChar->DecreaseCoin(itemInfo.price * (currentAmount - remainedCount));
		}
	}
}
