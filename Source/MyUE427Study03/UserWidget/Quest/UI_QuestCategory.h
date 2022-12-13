// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "MyUE427Study03/Quest/QuestEnum.h"
#include "UI_QuestCategory.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_QuestCategory : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Expand;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_CategoryName;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VBOX_QuestBox;

	UPROPERTY(EditAnywhere)
	EQuestStates currentStates = EQuestStates::CurrentQuest;

private:
	bool bIsExpand = false;
	
public:
	virtual void NativeConstruct() override;

	void SetCategoryName(FText text);

	UFUNCTION()
	void OnExpandButtonClicked();
};
