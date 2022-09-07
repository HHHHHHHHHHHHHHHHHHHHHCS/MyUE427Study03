// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Quest_Quest.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_Quest_Quest : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Meta=(BindWidget))
	class UTextBlock* Text_QuestName;

	UPROPERTY(Meta=(BindWidget))
	class UVerticalBox* VBOX_SubGoal;
	
};
