// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Quest_Journal.h"

#include "UI_Quest_GoalEntry.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/Others/StaticLibrary.h"
#include "MyUE427Study03/Quest/QuestBase.h"

#define LOCTEXT_NAMESPACE "UUI_Quest_Journal"

void UUI_Quest_Journal::UpdateSuggestedLevelColor()
{
	int playerLevel = playerChar->GetCurrentLevel();
	int questLevel = selectedQuest->questInfo.suggestedLevel;

	FLinearColor tempColor;

	if (playerLevel > questLevel)
	{
		tempColor = FLinearColor::Green;
	}
	else if (playerLevel == questLevel)
	{
		tempColor = FLinearColor::White;
	}
	else
	{
		tempColor = FLinearColor::Red;
	}
	Text_SuggestedLevel->SetColorAndOpacity(tempColor);
}

void UUI_Quest_Journal::UpdateDesc()
{
	Text_Description->SetText(FText::FromString(selectedQuest->currentDescription.ToString().Replace(TEXT("\n"),TEXT(" "))));
}

void UUI_Quest_Journal::GenerateSubGoals()
{
	for (FCompletedGoal& completedGoal : selectedQuest->completedSubGoals)
	{
		UClass* cls = LoadClass<UUI_Quest_GoalEntry>(GetWorld(),TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Quest/UI_Quest_GoalEntry.UI_Quest_GoalEntry_C'"));
		UUI_Quest_GoalEntry* goalEntryUI = CreateWidget<UUI_Quest_GoalEntry>(GetWorld(), cls);
		goalEntryUI->goalInfo = completedGoal.goalInfo;
		goalEntryUI->journalUI = this;
		goalEntryUI->goalStates = completedGoal.bSuccessful ? EGoalStates::Success : EGoalStates::Failed;
		VBox_QuestGoals->AddChildToVerticalBox(goalEntryUI);
	}

	for (FGoalInfo& item : selectedQuest->currentGoals)
	{
		UClass* cls = LoadClass<UUI_Quest_GoalEntry>(GetWorld(),TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Quest/UI_Quest_GoalEntry.UI_Quest_GoalEntry_C'"));
		UUI_Quest_GoalEntry* goalEntryUI = CreateWidget<UUI_Quest_GoalEntry>(GetWorld(), cls);
		goalEntryUI->goalInfo = item;
		goalEntryUI->journalUI = this;
		goalEntryUI->goalStates = EGoalStates::Current;
		VBox_QuestGoals->AddChildToVerticalBox(goalEntryUI);
	}
}

void UUI_Quest_Journal::UpdateDetailWindow()
{
	if (selectedQuest)
	{
		Text_QuestName->SetText(selectedQuest->questInfo.name);
		Text_QuestCategory->SetText(FText::FromString(UStaticLibrary::GetEnumValueAsString("EQuestCategories", selectedQuest->questInfo.category)));

		FLinearColor tempColor;
		switch (selectedQuest->questInfo.category)
		{
		case EQuestCategories::MainQuest:
			{
				tempColor = FLinearColor(1, 0.37, 0, 1);
				break;
			}
		case EQuestCategories::SideQuest:
			{
				tempColor = FLinearColor(0.45, 0.47, 1, 1);
				break;
			}
		case EQuestCategories::Events:
			{
				tempColor = FLinearColor(1, 0.19, 0.13, 1);
				break;
			}
		}
		Text_QuestCategory->SetColorAndOpacity(tempColor);
		Text_QuestRegion->SetText(FText::FromString(UStaticLibrary::GetEnumValueAsString("Regions", selectedQuest->questInfo.region)));
		Text_SuggestedLevel->SetText(FText::AsNumber(selectedQuest->questInfo.suggestedLevel));
		UpdateSuggestedLevelColor();

		int experience = selectedQuest->questInfo.completionReward.experience;
		int gold = selectedQuest->questInfo.completionReward.gold;

		if (experience > 0)
		{
			HBOX_ExpReward->SetVisibility(ESlateVisibility::Visible);
			Text_ExpReward->SetText(FText::Format(LOCTEXT("UUI_Quest_Journal", "+{0} Exp"), FText::AsNumber(experience)));
		}
		else
		{
			HBOX_ExpReward->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (gold > 0)
		{
			HBOX_GoldReward->SetVisibility(ESlateVisibility::Visible);
			Text_GoldReward->SetText(FText::Format(LOCTEXT("UUI_Quest_Journal", "+{0} Gold"), FText::AsNumber(gold)));
		}
		else
		{
			HBOX_GoldReward->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (experience > 0 && gold > 0)
		{
			VBox_RewardDetail->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			VBox_RewardDetail->SetVisibility(ESlateVisibility::Collapsed);
		}

		UpdateDesc();
		GenerateSubGoals();

		if (selectedQuest->currentState == EQuestStates::CurrentQuest)
		{
			HBox_Button->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			Button_Cancel->SetVisibility(ESlateVisibility::Collapsed);
		}
		
		SBox_QuestDetail->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SBox_QuestDetail->SetVisibility(ESlateVisibility::Hidden);
	}
}
#undef LOCTEXT_NAMESPACE
