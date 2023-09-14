// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_ManaPotion.h"

#include "Inventory.h"
#include "MyUE427Study03/Characters/CharacterBase.h"

void AItem_ManaPotion::OnUsed()
{
	auto player = inventoryRef->playerChar;
	if (player->GetCurrentMP() >= player->GetTotalMP())
	{
		Destroy();
		return;
	}

	inventoryRef->playerChar->ChangeCurrentMP(mpValue);
	inventoryRef->RemoveItemAtIndex(index, 1);
	Destroy();
}

