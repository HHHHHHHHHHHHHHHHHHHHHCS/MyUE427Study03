// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UI_BuffWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_BuffWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	UImage* Image_BuffIcon;

	UPROPERTY(meta=(BindWidget))
	UImage* Image_RemainingTime;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_RemaingTime;

	UTexture2D* buffTexure;

	UMaterialInstanceDynamic* cooldownMat;

public:
	virtual void NativeConstruct() override;
};
