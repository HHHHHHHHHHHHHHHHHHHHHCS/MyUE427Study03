// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "UI_Quest_GoalEntry.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_Quest_GoalEntry : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	UImage* Image_GoalState;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_GoalDesc;

public:
	void SetGoalText(FText text);
};
