// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Quest_GoalEntry.h"

#include "Components/TextBlock.h"

void UUI_Quest_GoalEntry::SetGoalText(FText text)
{
	Text_GoalDesc->SetText(text);
}
