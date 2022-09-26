// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "UI_Quest_Quest.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_Quest_Quest : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta=(BindWidget))
	UTextBlock* Text_QuestName;

	UPROPERTY(Meta=(BindWidget))
	UVerticalBox* VBOX_SubGoal;

	class AQuestManager* questManager;
	class AQuestBase* assignedQuest;
	TArray<class UUI_Quest_SubGoal*> subGoalWidgets;
	UUI_Quest_SubGoal* selectSubGoalWidget;

	void GenerateSubWidgets();

	void UpdateQuest();

	bool BCurrentQuest();

	void SelectSubGoal(UUI_Quest_SubGoal* clickedSubGoalUI);

	void OnQuestSelected(UUI_Quest_SubGoal* subGoalWidget);
};
