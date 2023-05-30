// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryEnum.generated.h"

UENUM()
enum class EItemCategories
{
	Consume,
	Equipment,
	QuestItem,
	Readable,
};

UENUM()
enum class ESortType
{
	Category,
	Amount,
	Name,
};

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UInventoryEnum : public UObject
{
	GENERATED_BODY()
};
