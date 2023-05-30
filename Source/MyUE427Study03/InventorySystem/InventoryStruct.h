// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryEnum.h"
#include "UObject/NoExportTypes.h"
#include "InventoryStruct.generated.h"

USTRUCT()
struct FItemInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="ItemInfo")
	FText name;

	UPROPERTY(EditAnywhere, Category="ItemInfo")
	FText desc;

	UPROPERTY(EditAnywhere, Category="ItemInfo")
	UTexture2D* icon;

	UPROPERTY(EditAnywhere, Category="ItemInfo")
	bool canUsed = true;

	UPROPERTY(EditAnywhere, Category="ItemInfo")
	FText useText; //使用说明, 比如: 药水-Drink, 地图-Read

	UPROPERTY(EditAnywhere, Category="ItemInfo")
	bool canStacked; //是否可以堆积

	UPROPERTY(EditAnywhere, Category="ItemInfo")
	EItemCategories category = EItemCategories::Consume;

	UPROPERTY(EditAnywhere, Category="ItemInfo")
	FString compareName;
};

USTRUCT()
struct FInventorySlot
{
	GENERATED_BODY()
public:
	TSubclassOf<class AItemBase> itemClass;
	int amount;
};

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UInventoryStruct : public UObject
{
	GENERATED_BODY()
};
