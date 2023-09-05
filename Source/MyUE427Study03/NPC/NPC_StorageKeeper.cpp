// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_StorageKeeper.h"

#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/InventorySystem/Storage.h"

void ANPC_StorageKeeper::OnInteractWith(ACharacterBase* character)
{
	character->storageRef->OpenStorage();
}

void ANPC_StorageKeeper::OnLeavePlayerRadius(ACharacterBase* character)
{
	character->storageRef->CloseStorage();
}
