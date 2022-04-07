// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_Main.h"

bool UUserWidget_Main::Initialize()
{
	bool isInit = Super::Initialize();
	if (!isInit)
	{
		return false;
	}

	levelText = Cast<UTextBlock>(GetWidgetFromName("Text_Level"));
	hpProgressBar = Cast<UProgressBar>(GetWidgetFromName("ProgressBar_Hp"));
	mpProgressBar = Cast<UProgressBar>(GetWidgetFromName("ProgressBar_Mp"));
	return true;
}

void UUserWidget_Main::SetLevelText(FText text)
{
	levelText->SetText(text);
}

void UUserWidget_Main::SetHpProgressBar(float percent)
{
	hpProgressBar->SetPercent(percent);
}

void UUserWidget_Main::SetMpProgressBar(float percent)
{
	mpProgressBar->SetPercent(percent);
}
