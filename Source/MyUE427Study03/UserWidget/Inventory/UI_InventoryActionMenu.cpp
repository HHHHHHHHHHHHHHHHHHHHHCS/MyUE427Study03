// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_InventoryActionMenu.h"

#include "Components/WrapBox.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "MyUE427Study03/InventorySystem/ItemBase.h"

void UUI_InventoryActionMenu::NativeConstruct()
{
	Super::NativeConstruct();
	Button_UseItem->OnClicked.AddDynamic(this, &UUI_InventoryActionMenu::OnButtonUseItemClick);
	Button_ThrowAway->OnClicked.AddDynamic(this, &UUI_InventoryActionMenu::OnButtonThrowAwayClick);
	Button_SplitStack->OnClicked.AddDynamic(this, &UUI_InventoryActionMenu::OnButtonSplitStackClick);
	Button_Cancel->OnClicked.AddDynamic(this, &UUI_InventoryActionMenu::OnButtonCancelClick);
}

void UUI_InventoryActionMenu::UpdateInfo(int index)
{
	currentIndex = index;
	itemInfo = inventoryRef->GetItemByIndex(index)->itemInfo;
	amount = inventoryRef->GetAmountAtIndex(index);

	if (itemInfo.canUsed)
	{
		Text_UseItem->SetText(itemInfo.useText);
		Button_UseItem->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Button_UseItem->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (amount > 1 && itemInfo.canStacked)
	{
		Button_SplitStack->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Button_SplitStack->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUI_InventoryActionMenu::OnButtonUseItemClick()
{
	inventoryRef->UseItemAtIndex(currentIndex);
	SetVisibility(ESlateVisibility::Hidden);
}

void UUI_InventoryActionMenu::OnButtonThrowAwayClick()
{
	if (!itemInfo.canStacked && amount > 0)
	{
		inventoryRef->RemoveItemAtIndex(currentIndex, 1);
	}
	else
	{
		auto mainUI = inventoryRef->playerChar->mainUI;
		mainUI->throwAwayWidget->UpdateInfo(currentIndex);
		mainUI->throwAwayWidget->SetVisibility(ESlateVisibility::Visible);
		mainUI->inventoryWidget->WBOX_Inventory->SetIsEnabled(false);
	}
	SetVisibility(ESlateVisibility::Hidden);
}

void UUI_InventoryActionMenu::OnButtonSplitStackClick()
{
	inventoryRef->SplitStack(currentIndex, amount / 2);
	SetVisibility(ESlateVisibility::Hidden);
}

void UUI_InventoryActionMenu::OnButtonCancelClick()
{
	SetVisibility(ESlateVisibility::Hidden);
}
