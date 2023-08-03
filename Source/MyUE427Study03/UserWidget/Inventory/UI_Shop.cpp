// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Shop.h"

#include "UI_ItemDragDropOperation.h"
#include "UI_OfferedItem.h"
#include "UI_SellItem.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"
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
	offeredItemWidgets.Empty();
	UGrid_OfferedItem->ClearChildren();
	for (int i = 0; i < merchant->offeredItems.Num(); i++)
	{
		auto cls = LoadClass<UUI_OfferedItem>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_OfferedItem.UI_OfferedItem_C'"));
		auto widget = CreateWidget<UUI_OfferedItem>(GetWorld(), cls);
		widget->Init(merchant->offeredItems[i], playerChar->inventoryRef, this);
		offeredItemWidgets.Add(widget);
		UGrid_OfferedItem->AddChildToUniformGrid(widget, i / 2, i % 2);
	}
}

void UUI_Shop::Click_ButtonClose()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UUI_Shop::UpdateAllItems()
{
	for (auto& item : offeredItemWidgets)
	{
		item->UpdatePrice();
	}
}

bool UUI_Shop::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	auto itemOp = Cast<UUI_ItemDragDropOperation>(InOperation);
	if (itemOp)
	{
		auto slotUI = itemOp->uiDragSlot;
		if (slotUI->itemInfo.category == EItemCategories::QuestItem)
		{
			return false;
		}
		else
		{
			if (!slotUI->itemInfo.canStacked && slotUI->amount > 0)
			{
				if(playerChar->inventoryRef->RemoveItemAtIndex(slotUI->slotIndex, 1))
				{
					playerChar->IncreaseCoin(slotUI->itemInfo.price);
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				UI_SellItem->UpdateInfo(slotUI->slotIndex);
				UI_SellItem->SetVisibility(Visibility);
				playerChar->mainUI->inventoryWidget->WBOX_Inventory->SetIsEnabled(false);
				return true;
			}

		}
	}
	else
	{
		return false;
	}

}
