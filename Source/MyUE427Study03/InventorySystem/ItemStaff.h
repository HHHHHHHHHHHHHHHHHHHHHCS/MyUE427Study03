// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "ItemStaff.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API AItemStaff : public AItemBase
{
	GENERATED_BODY()

public:
	AItemStaff();

public:
	UPROPERTY(EditDefaultsOnly, category="Item")
	FString socketName;

public:
	virtual void OnUsed() override;
};
