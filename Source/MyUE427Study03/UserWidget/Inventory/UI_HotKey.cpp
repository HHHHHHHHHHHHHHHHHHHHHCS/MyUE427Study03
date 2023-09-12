// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_HotKey.h"

void UUI_HotKey::Init(FKey _key, AInventory* _inventoryRef)
{
	key = _key;
	inventoryRef = _inventoryRef;
	Text_HotKey->SetText(key.GetDisplayName());
}
