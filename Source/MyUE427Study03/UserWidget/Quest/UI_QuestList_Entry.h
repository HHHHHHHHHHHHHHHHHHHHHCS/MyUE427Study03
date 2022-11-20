// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI_QuestList_Entry.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_QuestList_Entry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_QuestName;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_RegionName;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_SuggestedtLv;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Quest;

public:
	void SetQuestName(FText questNameText);

	void SetRegionName(FText regionNameText);

	void SetSuggestedLevel(FText levelText);
};
