// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryEnum.generated.h"

UENUM()
enum class EItemCategories
{
	Consume = 0,
	Equipment,
	QuestItem,
	Readable,
	Material, //合成物品的材料
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
