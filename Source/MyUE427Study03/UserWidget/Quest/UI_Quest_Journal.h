// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_QuestCategory.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
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
	UScrollBox* SBox_QuestList;

	UPROPERTY(meta=(BindWidget))
	UScrollBox* SBox_QuestDetail;

	UPROPERTY(meta=(BindWidget))
	UUI_QuestCategory* UI_QuestCategory_Current;

	UPROPERTY(meta=(BindWidget))
	UUI_QuestCategory* UI_QuestCategory_Completed;

	UPROPERTY(meta=(BindWidget))
	UUI_QuestCategory* UI_QuestCategory_Failed;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_QuestName;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_QuestCategory;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_QuestRegion;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_SuggestedLevel;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VBox_RewardDetail;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_ExpReward;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_GoldReward;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Description;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VBox_QuestGoals;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* HBox_Button;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Select;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Cancel;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* HBOX_ExpReward;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* HBOX_GoldReward;

	class AQuestBase* selectedQuest;

	class ACharacterBase* playerChar;

public:
	void UpdateSuggestedLevelColor();

	void UpdateDesc();

	void GenerateSubGoals();

	void UpdateDetailWindow();
};
