// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UI_HotKey.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_HotKey : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta=(BindWidget))
	UTextBlock* Text_HotKey;

	UPROPERTY(Meta=(BindWidget))
	class UUI_ItemHotKey* ItemHotKeySlot;

	FKey key;

	class AInventory* inventoryRef;


public:
	void Init(FKey _key, class AInventory* _inventoryRef);
};
