// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Quest_Quest.h"

#include "UI_Quest_SubGoal.h"
#include "Components/VerticalBox.h"

void UUI_Quest_Quest::GenerateSubWidgets()
{
	subGoalWidgets.Empty();
	VBOX_SubGoal->ClearChildren();
	for (FGoalInfo goalInfo : assignedQuest->currentGoals)
	{
		UClass* cls = LoadClass<UUI_Quest_SubGoal>(GetWorld(),TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Quest/UI_SubGoal.UI_SubGoal_C'"));
		UUI_Quest_SubGoal* subGoalWidget = CreateWidget<UUI_Quest_SubGoal>(GetWorld(), cls);
		subGoalWidget->goalInfo = goalInfo;
		subGoalWidget->assignedQuest = assignedQuest;
		subGoalWidget->questWidget = this;

		subGoalWidgets.Add(subGoalWidget);
		VBOX_SubGoal->AddChild(subGoalWidget);
	}
}

void UUI_Quest_Quest::UpdateQuest()
{
	if (assignedQuest)
	{
		Text_QuestName->SetText(assignedQuest->questInfo.name);

		FLinearColor tempColor;
		switch (assignedQuest->questInfo.category)
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
		Text_QuestName->SetColorAndOpacity(tempColor);
		GenerateSubWidgets();
	}
}

bool UUI_Quest_Quest::BCurrentQuest()
{
	return assignedQuest == questManager->currentQuest;
}
