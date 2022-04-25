// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SkillHotkey.h"

#include "MyUE427Study03/Skill/SkillBase.h"

bool UUI_SkillHotkey::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	Button_Skill->OnClicked.AddDynamic(this, &UUI_SkillHotkey::OnSKillButtonClicked);

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

void UUI_SkillHotkey::ClearAssignedSpell()
{
	if (assignedSpell)
	{
		assignedSpell->SetHotkey(nullptr);
		assignedSpell = nullptr;

		Image_SkillIcon->SetIsEnabled(false);
		Image_SkillIcon->SetBrushFromTexture(nullptr);
		Image_SkillIcon->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUI_SkillHotkey::OnSKillButtonClicked()
{
	assignedSpell->OnTryCastSpell();
}

void UUI_SkillHotkey::EnableHotkey()
{
	bIsActive = true;
	if(assignedSpell->IsCooldown())
	{
		//TODO:
	}
}

void UUI_SkillHotkey::DisableHotkey()
{
	bIsActive = false;

}
