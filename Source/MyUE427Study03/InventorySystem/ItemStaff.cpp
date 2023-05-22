// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemStaff.h"

#include "Inventory.h"
#include "MyUE427Study03/Characters/CharacterBase.h"

void AItemStaff::OnUsed()
{
	if(!inventoryRef->playerChar->EquipItem(this))
	{
		Destroy();
	}
}
