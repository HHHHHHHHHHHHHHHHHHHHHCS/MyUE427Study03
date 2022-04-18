// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_Main.h"

#include "UI_HotkeyRow.h"

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
	hotkeyRowContainer = Cast<UVerticalBox>(GetWidgetFromName("HotkeyRowContainer"));
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

void UUserWidget_Main::GenerateHotkeys(TArray<FKey> keys, int keysPerRow)
{
	if (keys.Num() % keysPerRow != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("The num of keys is invalid!"));
		return;
	}

	UClass* cls = LoadClass<UUI_HotkeyRow>(
		GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Skill/UI_HotkeyRow.UI_HotkeyRow_C'"));
	if (cls == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UUI_HotkeyRow class not found!"));
		return;
	}

	if (keys.Num() == keysPerRow)
	{
		UUI_HotkeyRow* row = CreateWidget<UUI_HotkeyRow>(GetWorld(), cls);
		row->SetHotkeys(keys);
		hotkeyRowContainer->AddChildToVerticalBox(row);
		allHotkeySlots.Append(row->GenerateHotkeys());
	}
}
