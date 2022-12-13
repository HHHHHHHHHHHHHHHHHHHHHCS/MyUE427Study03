// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_QuestList_Entry.h"

#include "UI_Quest_Journal.h"
#include "MyUE427Study03/Characters/CharacterBase.h"

void UUI_QuestList_Entry::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateQuestInfo();
}

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

void UUI_QuestList_Entry::UpdateQuestInfo()
{
	if (assignedQuest->questInfo.name.ToString().Len() < 20)
	{
		SetQuestName(assignedQuest->questInfo.name);
	}
	else
	{
		SetQuestName(FText::FromString(assignedQuest->questInfo.name.ToString().LeftChop(assignedQuest->questInfo.name.ToString().Len() - 17).Append("...")));
	}
	SetSuggestedLevel(FText::AsNumber(assignedQuest->questInfo.suggestedLevel));
	UpdateLevelColor();
	//枚举转换成字符串
	SetRegionName(FText::FromString(GetRegionEnumString(assignedQuest->questInfo.region)));
}

FString UUI_QuestList_Entry::GetRegionEnumString(ERegions region)
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ERegions"), true);
	if (!enumPtr)
	{
		return FString("InValid");
	}
	FString str = enumPtr->GetNameStringByValue((int64)region);
	str.RemoveFromStart("ERegions::");
	return str;
}
