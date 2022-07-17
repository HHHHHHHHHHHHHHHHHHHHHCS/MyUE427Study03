// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SkillTree_Connection.h"

void UUI_SkillTree_Connection::Active()
{
	if(!bActive)
	{
		bActive = true;
		Image_Line->SetOpacity(0.7f);
	}
}
