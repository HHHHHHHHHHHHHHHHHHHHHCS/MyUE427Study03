// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Inventory.h"

#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"

void UUI_Inventory::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Close->OnClicked.AddDynamic(this, &UUI_Inventory::OnCloseButtonClick);
}

void UUI_Inventory::GenerateSlotWidget()
{
	WBOX_Inventory->ClearChildren();
	inventorySlots.Empty();
	auto* slotCls = LoadClass<UUI_InventorySlot>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_InventorySlot.UI_InventorySlot_C'"));
	for (int i = 0; i < inventoryRef->slots.Num(); i++)
	{
		UUI_InventorySlot* slotUI = CreateWidget<UUI_InventorySlot>(GetWorld(), slotCls);
		slotUI->inventoryRef = inventoryRef;
		slotUI->slotIndex = i;
		slotUI->UpdateSlot();
		WBOX_Inventory->AddChild(slotUI);
		inventorySlots.Add(slotUI);
	}
}

void UUI_Inventory::OnCloseButtonClick()
{
	if (bInventoryShow)
	{
		SetVisibility(ESlateVisibility::Hidden);
		bInventoryShow = false;
	}
}

void UUI_Inventory::ToggleVisibility()
{
	if (bInventoryShow)
	{
		SetVisibility(ESlateVisibility::Hidden);
		bInventoryShow = false;
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
		bInventoryShow = true;
	}
}
