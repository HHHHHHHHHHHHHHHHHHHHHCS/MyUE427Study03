// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SkillHotkey.h"

#include "MyUE427Study03/Skill/SkillBase.h"

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
	if (!bHasSetKeyName)
	{
		bHasSetKeyName = true;
		Text_Hotkey->SetText(key.GetDisplayName());
	}
}

void UUI_SkillHotkey::AssignSpell(ASkillBase* newAssignedSpell)
{
	this->assignedSpell = newAssignedSpell;
	assignedSpell->SetHotkey(this);
	Button_Skill->SetIsEnabled(true);
	if (assignedSpell->GetCurrentStage().overrideIcon)
	{
		Image_SkillIcon->SetBrushFromTexture(assignedSpell->GetCurrentStage().overrideIcon);
	}
	else
	{
		Image_SkillIcon->SetBrushFromTexture(assignedSpell->skillInfo.icon);
	}
	Image_SkillIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}
