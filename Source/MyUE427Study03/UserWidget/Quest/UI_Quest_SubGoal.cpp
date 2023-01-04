// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Quest_SubGoal.h"

#include "MyUE427Study03/Quest/QuestManager.h"

#define LOCTEXT_NAMESPACE "UI_Quest_SubGoal"

void UUI_Quest_SubGoal::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Select->OnClicked.AddDynamic(this, &UUI_Quest_SubGoal::OnSelectButtonClicked);
	Update();
}

void UUI_Quest_SubGoal::Update()
{
	if (goalInfo.bCustomGoal)
	{
		Text_Goal->SetText(goalInfo.goalText);
	}
	else
	{
		FText tempText;
		switch (goalInfo.type)
		{
		case EGoalTypes::Custom:
			{
				tempText = goalInfo.goalText;
				break;
			}
		case EGoalTypes::Hunt:
			{
				tempText = FText::Format(LOCTEXT("UI_Quest_SubGoal", "Hunt {0}{1}:{2}/{3}"),
				                         goalInfo.additionalName,
				                         FText::FromString(goalInfo.amountToHunt > 1 ? "s" : ""),
				                         FText::AsNumber(assignedQuest->currentHuntedAmount),
				                         FText::AsNumber(goalInfo.amountToHunt));
				break;
			}
		case EGoalTypes::Find:
			{
				tempText = FText::Format(LOCTEXT("SubGoalWidget", "Find the {0}"), goalInfo.additionalName);
				break;
			}
		case EGoalTypes::Talk:
			{
				tempText = FText::Format(LOCTEXT("SubGoalWidget", "Talk the {0}"), goalInfo.additionalName);
				break;
			}
		default: break;
		}
		Text_Goal->SetText(tempText);
	}

	for (int i = 0; i < assignedQuest->questInfo.subGoals.Num(); i++)
	{
		if (assignedQuest->questInfo.subGoals[i] == goalInfo)
		{
			goalIndex = i;
		}
	}
}

void UUI_Quest_SubGoal::OnSelectButtonClicked()
{
	if (questWidget->BCurrentQuest())
	{
		questWidget->SelectSubGoal(this);
	}
	else
	{
		questWidget->questManager->SelectNewQuest(assignedQuest, this);
	}
}


#undef LOCTEXT_NAMESPACE
