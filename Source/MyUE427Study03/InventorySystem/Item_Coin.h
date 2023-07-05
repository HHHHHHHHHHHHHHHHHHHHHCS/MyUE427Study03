// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Item_Coin.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API AItem_Coin : public AItemBase
{
	GENERATED_BODY()

public:
	virtual void OnInteractWith(ACharacterBase* character) override;
};
