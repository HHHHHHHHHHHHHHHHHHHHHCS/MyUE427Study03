// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Quest_SubGoal.h"

void UUI_Quest_SubGoal::Update()
{
	if (goalInfo.bCustomGoal)
	{
		Text_Goal->SetText(goalInfo.goalText);
	}
	else
	{
		FText tempText;
		//TODO:
		switch (goalInfo.type)
		{
		case EGoalTypes::Custom:
			tempText = goalInfo.goalText;
			break;
		case EGoalTypes::Hunt: break;
		case EGoalTypes::Find: break;
		case EGoalTypes::Talk: break;
		default: break;
		}
	}
}
