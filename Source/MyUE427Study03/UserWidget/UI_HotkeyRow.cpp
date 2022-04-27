// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_HotkeyRow.h"

TArray<UUI_SkillHotkey*> UUI_HotkeyRow::GenerateHotkeys(int row)
{
	UClass* clsLoad = LoadClass<UUI_SkillHotkey>(
		GetWorld(),TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Skill/UI_SkillHotkey.UI_SkillHotkey_C'"));


	if (clsLoad == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UI_SkillHotkey class not found!"));
		return slotWidgets;
	}

	int index = 0;
	for (const auto& key : keys)
	{
		UUI_SkillHotkey* skillHotkey = CreateWidget<UUI_SkillHotkey>(GetWorld(), clsLoad);
		skillHotkey->hotkeyIndex = index++;
		skillHotkey->hotkeyRow = row;
		skillHotkey->SetKey(key);
		slotWidgets.Add(skillHotkey);
		RowBox->AddChildToHorizontalBox(skillHotkey);
	}

	return slotWidgets;
}
