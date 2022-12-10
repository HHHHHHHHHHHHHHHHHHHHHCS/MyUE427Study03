// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_Quest_Journal.h"
#include "Blueprint/UserWidget.h"
#include "MyUE427Study03/Quest/QuestStruct.h"
#include "UI_Quest_GoalEntry.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_Quest_GoalEntry : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	UImage* Image_GoalState;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_GoalDesc;

	FGoalInfo goalInfo;

	EGoalStates goalStates;

	UUI_Quest_Journal* journalUI;

	UPROPERTY(EditAnywhere, Category="StateIcon")
	UTexture2D* currentTex2D;

	UPROPERTY(EditAnywhere, Category="StateIcon")
	UTexture2D* successTex2D;

	UPROPERTY(EditAnywhere, Category="StateIcon")
	UTexture2D* failedTex2D;

public:
	virtual void NativeConstruct() override;

	void SetGoalText(FText text);

	void Update();
};
