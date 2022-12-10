// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_QuestList_Entry.h"

#include "UI_Quest_Journal.h"
#include "MyUE427Study03/Characters/CharacterBase.h"

void UUI_QuestList_Entry::SetQuestName(FText questNameText)
{
	Text_QuestName->SetText(questNameText);
}

void UUI_QuestList_Entry::SetRegionName(FText regionNameText)
{
	Text_RegionName->SetText(regionNameText);
}

void UUI_QuestList_Entry::SetSuggestedLevel(FText levelText)
{
	Text_SuggestedtLv->SetText(levelText);
}

void UUI_QuestList_Entry::UpdateLevelColor()
{
	int playerLevel = questJournal->playerChar->GetCurrentLevel();
	int questLevel = assignedQuest->questInfo.suggestedLevel;

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
	Text_SuggestedtLv->SetColorAndOpacity(tempColor);
}
