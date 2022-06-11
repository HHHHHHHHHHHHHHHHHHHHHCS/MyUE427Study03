// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_SkillHotkey.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
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

	UVerticalBox* hotkeyRowContainer;
	
	TArray<UUI_SkillHotkey*> allHotkeySlots;

	UTextBlock * enemyNameLevelText;

	UTextBlock * enemyHpText;

	UProgressBar* enemyHpProgressBar;
	
public:
	virtual bool Initialize() override;

	void SetLevelText(FText text);

	void SetHpProgressBar(float percent);

	void SetMpProgressBar(float percent);

	void GenerateHotkeys(TArray<FKey> keys, int keysPerRow);

	FORCEINLINE TArray<UUI_SkillHotkey*> GetAllHotKeySlots()
	{
		return allHotkeySlots;
	};

	UFUNCTION(BlueprintNativeEvent, Category="Animation")
	void PlayPopupAnimation();

	void PlayPopupAnimation_Implementation();

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
