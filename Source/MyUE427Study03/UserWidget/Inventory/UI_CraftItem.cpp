// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CraftItem.h"

#include "UI_CraftMenu.h"
#include "MyUE427Study03/InventorySystem/ItemBase.h"

void UUI_CraftItem::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Selected->OnClicked.AddDynamic(this, &UUI_CraftItem::Click_Selected);
}

void UUI_CraftItem::OnInit(TSubclassOf<AItemBase> _item, UUI_CraftMenu* _craftMenu)
{
	item = _item;
	craftMenu = _craftMenu;
	Text_Name->SetText(item->GetDefaultObject<AItemBase>()->itemInfo.name);
}

void UUI_CraftItem::Click_Selected()
{
	craftMenu->Click_OnCraft(this);
}
