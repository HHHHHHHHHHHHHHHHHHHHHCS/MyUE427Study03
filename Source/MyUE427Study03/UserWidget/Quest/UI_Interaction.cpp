// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Interaction.h"

void UUI_Interaction::SetNameText(FText name)
{
	Text_Name->SetText(name);
}

void UUI_Interaction::SetInteractionText(FText name)
{
	Text_Interaction->SetText(name);
}