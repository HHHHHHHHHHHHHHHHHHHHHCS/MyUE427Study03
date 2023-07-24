// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Shop.h"

#include "UI_OfferedItem.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/NPC/NPC_Merchant.h"

void UUI_Shop::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Close->OnClicked.AddDynamic(this, &UUI_Shop::Click_ButtonClose);
}

void UUI_Shop::UpdateCoin()
{
	Text_Coin->SetText(FText::AsNumber(playerChar->GetCurrentCoin()));
}

void UUI_Shop::GenerateItemList()
{
	for (int i = 0; i < merchant->offeredItems.Num(); i++)
	{
		auto cls = LoadClass<UUI_OfferedItem>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_OfferedItem.UI_OfferedItem_C'"));
		auto widget = CreateWidget<UUI_OfferedItem>(GetWorld(), cls);
		widget->Init(merchant->offeredItems[i], playerChar->inventoryRef);
		offeredItemWidgets.Add(widget);
		UGrid_OfferedItem->AddChildToUniformGrid(widget, i / 2, i % 2);
	}
}

void UUI_Shop::Click_ButtonClose()
{
	this->RemoveFromParent();
}
