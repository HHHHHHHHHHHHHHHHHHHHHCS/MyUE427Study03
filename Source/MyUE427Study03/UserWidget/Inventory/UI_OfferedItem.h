// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_OfferedItem.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_OfferedItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_Price;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_Amount;

	UPROPERTY(meta=(BindWidget))
	class UImage* Image_Icon;

	UPROPERTY(meta=(BindWidget))
	class UButton* Button_Buy;

	UPROPERTY(meta=(BindWidget))
	class USlider* Slider_Amount;
};
