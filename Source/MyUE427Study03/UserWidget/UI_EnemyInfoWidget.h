// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "UI_EnemyInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_EnemyInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* LevelName;
	UProgressBar* HealthBar;
};
