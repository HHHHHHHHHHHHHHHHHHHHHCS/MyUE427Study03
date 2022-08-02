// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI_Quest_SubGoal.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_Quest_SubGoal : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Select;

	UPROPERTY(Meta=(BindWidget))
	UBorder* Border_Goal;

	UPROPERTY(Meta=(BindWidget))
	UTextBlock* Text_Goal;
};
