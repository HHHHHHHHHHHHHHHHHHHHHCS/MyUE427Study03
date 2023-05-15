// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMap.h"

#include "Inventory.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/UserWidget/Inventory/UI_ItemReadable.h"

void AItemMap::OnUsed()
{
	inventoryRef->playerChar->mainUI->inventoryWidget->SetIsEnabled(false);
	auto cls = LoadClass<UUI_ItemReadable>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_ItemReadable.UI_ItemReadable_C'"));
	readableItemUI = CreateWidget<UUI_ItemReadable>(GetWorld(), cls);
	inventoryRef->playerChar->mainUI->readableContainer->AddChild(readableItemUI);
	FInputModeUIOnly inputMode;
	inventoryRef->playerChar->playerController->SetInputMode(inputMode);
}

void AItemMap::OnReaderEnd()
{
	inventoryRef->playerChar->mainUI->inventoryWidget->SetIsEnabled(true);
	if(readableItemUI)
	{
		readableItemUI->RemoveFromParent();
	}
	FInputModeGameAndUI inputMode;
	inventoryRef->playerChar->playerController->SetInputMode(inputMode);
}
