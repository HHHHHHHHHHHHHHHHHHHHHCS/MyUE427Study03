// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SkillHotkey.h"

bool UUI_SkillHotkey::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}


	return true;
}

void UUI_SkillHotkey::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if(!bHasSetKeyName)
	{
		bHasSetKeyName = true;
		Text_Hotkey->SetText(key.GetDisplayName());
	}
}
