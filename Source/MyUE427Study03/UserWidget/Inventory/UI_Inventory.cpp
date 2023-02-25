// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Inventory.h"

#include "Components/WrapBox.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"

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
