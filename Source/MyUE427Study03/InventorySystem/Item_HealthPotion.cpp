// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_HealthPotion.h"

#include "Inventory.h"
#include "MyUE427Study03/Characters/CharacterBase.h"

void AItem_HealthPotion::OnUsed()
{
	auto player = inventoryRef->playerChar;
	if (player->GetCurrentHP() >= player->GetTotalMP())
	{
		Destroy();
		return;
	}

	inventoryRef->playerChar->ChangeCurrentHP(hpValue);
	inventoryRef->RemoveItemAtIndex(index, 1);
	Destroy();
}
