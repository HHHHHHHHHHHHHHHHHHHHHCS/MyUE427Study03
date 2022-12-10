// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Quest_GoalEntry.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyUE427Study03/Quest/QuestBase.h"

#define LOCTEXT_NAMESPACE "UI_Quest_Journal"

void UUI_Quest_GoalEntry::NativeConstruct()
{
	Super::NativeConstruct();
	Update();
}

void UUI_Quest_GoalEntry::SetGoalText(FText text)
{
	Text_GoalDesc->SetText(text);
}

void UUI_Quest_GoalEntry::Update()
{
	if (goalInfo.bCustomGoal)
	{
		SetGoalText(goalInfo.goalText);
	}
	else
	{
		FText tempText;
		FText bs;
		switch (goalInfo.type)
		{
		case EGoalTypes::Custom:
			tempText = goalInfo.goalText;
			break;
		case EGoalTypes::Hunt:
			if (goalInfo.amountToHunt > 1)
			{
				bs = FText::FromString("s");
			}
			else
			{
				bs = FText::FromString("");
			}
			tempText = FText::Format(LOCTEXT("UI_Quest_Journal", "Hunt {0} {1}: {2}/ {3}"),
			                         goalInfo.additionalName, bs,
			                         FText::AsNumber(journalUI->selectedQuest->currentHuntedAmount),
			                         FText::AsNumber(goalInfo.amountToHunt));
			break;
		case EGoalTypes::Find:
			tempText = FText::Format(LOCTEXT("UI_Quest_Journal", "Find to {0}"), goalInfo.additionalName);
			break;
		case EGoalTypes::Talk:
			tempText = FText::Format(LOCTEXT("UI_Quest_Journal", "Talk to {0}"), goalInfo.additionalName);
			break;
		}
		SetGoalText(tempText);
	}

	UTexture2D* tempTex2D = nullptr;
	switch (goalStates)
	{
	case EGoalStates::Current:
		tempTex2D = currentTex2D;
		break;
	case EGoalStates::Success:
		tempTex2D = successTex2D;
		break;
	case EGoalStates::Failed:
		tempTex2D = failedTex2D;
		break;
	}

	if(tempTex2D)
	{
		Image_GoalState->SetBrushFromTexture(tempTex2D);
	}
}

#undef LOCTEXT_NAMESPACE
