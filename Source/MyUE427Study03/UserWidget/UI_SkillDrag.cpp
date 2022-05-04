// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SkillDrag.h"

void UUI_SkillDrag::SetSkillIconTexture(UTexture2D* texture)
{
	Image_SkillIcon->SetBrushFromTexture(texture);
}
