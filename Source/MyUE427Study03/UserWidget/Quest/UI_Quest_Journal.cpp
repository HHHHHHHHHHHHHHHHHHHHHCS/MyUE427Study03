// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Quest_Journal.h"

#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/Quest/QuestBase.h"

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
