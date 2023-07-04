// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CraftMenu.h"
#include "UI_CraftItem.h"
#include "UI_RecipeEntry.h"
#include "Components/Border.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "MyUE427Study03/InventorySystem/ItemBase.h"

void UUI_CraftMenu::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Close->OnClicked.AddDynamic(this, &UUI_CraftMenu::Click_OnClose);
	Button_Craft->OnClicked.AddDynamic(this, &UUI_CraftMenu::Click_OnCraft);
}

void UUI_CraftMenu::Click_OnCraft(class UUI_CraftItem* widget)
{
	if (currentCraft)
	{
		currentCraft->Button_Selected->SetIsEnabled(true);
	}

	currentCraft = widget;
	currentCraft->Button_Selected->SetIsEnabled(false);
	UpdateDetailWindow(widget->item);
}

void UUI_CraftMenu::Click_OnClose()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UUI_CraftMenu::Click_OnCraft()
{
	if (inventory->AddItem(currentItem, 1) <= 0)
	{
		for (auto slot : currentItemInfo.recipes)
		{
			inventory->RemoveItem(slot.itemClass, slot.amount);
		}
	}
	Button_Craft->SetIsEnabled(CanBeCrafted());
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
		entry->Update();
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

void UUI_CraftMenu::UpdateDetailWindow(TSubclassOf<AItemBase> item)
{
	if (item)
	{
		if (item == currentItem)
		{
			for (auto entry : recipeEntries)
			{
				entry->Update();
			}
			Button_Craft->SetIsEnabled(CanBeCrafted());
			Border_Detail->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			currentItem = item;
			currentItemInfo = item->GetDefaultObject<AItemBase>()->itemInfo;
			Image_Icon->SetBrushFromTexture(currentItemInfo.icon);
			Text_Name->SetText(currentItemInfo.name);
			Text_Desc->SetText(currentItemInfo.desc);
			GenerateRecipeEntries();
			Button_Craft->SetIsEnabled(CanBeCrafted());
			Border_Detail->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		currentItem = nullptr;
		recipeEntries.Empty();
		VBox_RecipeEntryList->ClearChildren();
		Border_Detail->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUI_CraftMenu::InitCraftMenu(AInventory* _inventory)
{
	inventory = _inventory;
	GenerateCraftItemList();
	UpdateDetailWindow(nullptr);
}
