// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyUE427Study03/InventorySystem/InventoryStruct.h"
#include "UI_ItemDetail.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_ItemDetail : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UImage* Image_Icon;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Name;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Amount;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Category;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Description;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_TotalWeight;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_SingleWeight;

public:
	FItemInfo itemInfo;
	int amount;

	void UpdateInfo();
};
