// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Minimap.h"

void UUI_Minimap::RotateDirectionArrow(float angle)
{
	Minimap_Arrow->SetRenderTransformAngle(angle);
}

void UUI_Minimap::SetDistanceText(float distance)
{
	Text_Distance->SetText(FText::AsNumber(distance));
}

void UUI_Minimap::SetGoalHitVisible(bool isVisible)
{
	if(isVisible)
	{
		Minimap_Arrow->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Text_Distance->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		Minimap_Arrow->SetVisibility(ESlateVisibility::Hidden);
		Text_Distance->SetVisibility(ESlateVisibility::Hidden);
	}
}
