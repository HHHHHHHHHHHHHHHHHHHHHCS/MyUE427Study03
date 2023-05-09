// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Item_HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API AItem_HealthPotion : public AItemBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="ItemInfo")
	int hpValue;

public:
	virtual void OnUsed() override;
};
