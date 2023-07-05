// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Coin.h"

#include "MyUE427Study03/Characters/CharacterBase.h"

void AItem_Coin::OnInteractWith(ACharacterBase* character)
{
	character->IncreaseCoin(amount);
	character->mainUI->AddItemToObtainedQueue(this->GetClass(), amount);
	Destroy();
}
