// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CraftMenu.h"

#include "UI_CraftItem.h"
#include "UI_RecipeEntry.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
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

void UUI_CraftMenu::GenerateRecipeEntries()
{
	VBox_RecipeEntryList->ClearChildren();
	recipeEntries.Empty();

	auto cls = LoadClass<UUI_RecipeEntry>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_RecipeEntry.UI_RecipeEntry_C'"));
	for (auto slot : currentItemInfo.recipes)
	{
		UUI_RecipeEntry* entry = CreateWidget<UUI_RecipeEntry>(GetWorld(), cls);
		entry->item = slot.itemClass;
		entry->requiredAmount = slot.amount;
		entry->craftMenu = this;
		recipeEntries.Add(entry);
		VBox_RecipeEntryList->AddChild(entry);
	}
}

bool UUI_CraftMenu::CanBeCrafted()
{
	for (auto widget : recipeEntries)
	{
		if (widget->currentAmount < widget->requiredAmount)
		{
			return false;
		}
	}

	return true;
}
