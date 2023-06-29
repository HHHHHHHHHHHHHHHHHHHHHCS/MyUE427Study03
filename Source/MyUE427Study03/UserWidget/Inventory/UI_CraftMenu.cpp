// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CraftMenu.h"

#include "UI_CraftItem.h"
#include "Components/ScrollBox.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"

void UUI_CraftMenu::Click_OnCraft(class UUI_CraftItem* widget)
{
}

void UUI_CraftMenu::GenerateCraftItemList()
{
	ScrollBox_CraftItems->ClearChildren();
	auto cls = LoadClass<UUI_CraftItem>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_CraftItem.UI_CraftItem_C'"));
	for (auto item : inventory->craftItems)
	{
		UUI_CraftItem* craftItemUI = CreateWidget<UUI_CraftItem>(GetWorld(), cls);
		craftItemUI->OnInit(item, this);
		ScrollBox_CraftItems->AddChild(craftItemUI);
	}
}
