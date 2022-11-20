// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_QuestList_Entry.h"

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
