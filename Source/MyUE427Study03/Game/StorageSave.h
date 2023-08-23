// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyUE427Study03/InventorySystem/InventoryStruct.h"
#include "StorageSave.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UStorageSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FInventorySlot> savedSlots;
};
