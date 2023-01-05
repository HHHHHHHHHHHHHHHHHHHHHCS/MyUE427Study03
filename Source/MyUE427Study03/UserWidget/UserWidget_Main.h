// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_Minimap.h"
#include "UI_SkillHotkey.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/ProgressBar.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
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

	UBorder* enemyBorder;

	UTextBlock* enemyNameLevelText;

	UTextBlock* enemyHpText;

	UProgressBar* enemyHpProgressBar;

	UHorizontalBox* buffBox;

	UProgressBar* expProgressBar;

	UTextBlock* expCurrText;

	UTextBlock* expMaxText;

	UUI_Minimap* minimapWidget;

	class UUI_SkillTree_MainTree* skillTree_MainTree;

	USizeBox* questListSizeBox;

	UScrollBox* questList;

	class AQuestManager* questManager;

	UPROPERTY(BlueprintReadOnly)
	TArray<class UUI_Quest_Quest*> questWidgetArray;

	UPROPERTY(BlueprintReadWrite)
	bool bOutSide = true;

	class UUI_Quest_Journal* questJournal;

	UButton* questButton;
	
private:

	bool bQuestUIVisibility = false;

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

	void SetExpPanel(float currExp, float maxExp);

	class UUI_Quest_Quest* AddQuestToList(class AQuestBase* quest);

	UFUNCTION()
	void OnQuestButtonClicked();
};
