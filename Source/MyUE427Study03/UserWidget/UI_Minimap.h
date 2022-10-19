// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UI_Minimap.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_Minimap : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UImage* Minimap_Arrow;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* Text_Distance;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UHorizontalBox* HBox_Distance;

public:
	void RotateDirectionArrow(float angle);
	
	void SetDistanceText(float distance);

	void SetGoalHitVisible(bool isVisible);
};
