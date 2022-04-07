// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "UserWidget_Main.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUserWidget_Main : public UUserWidget
{
	GENERATED_BODY()


public:
	UTextBlock* levelText;

	UProgressBar* hpProgressBar;

	UProgressBar* mpProgressBar;

public:
	virtual bool Initialize() override;

	void SetLevelText(FText text);

	void SetHpProgressBar(float percent);

	void SetMpProgressBar(float percent);
};
