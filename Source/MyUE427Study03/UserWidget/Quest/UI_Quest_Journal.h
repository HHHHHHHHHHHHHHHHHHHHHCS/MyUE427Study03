// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_QuestCategory.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "UI_Quest_Journal.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_Quest_Journal : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UScrollBox* SBOX_QuestList;

	UPROPERTY(meta=(BindWidget))
	UUI_QuestCategory* UI_QuestCategory_Current;

	UPROPERTY(meta=(BindWidget))
	UUI_QuestCategory* UI_QuestCategory_Completed;

	UPROPERTY(meta=(BindWidget))
	UUI_QuestCategory* UI_QuestCategory_Failed;
	
};
