// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UI_Quest_Message.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_Quest_Message : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta =(BindWidget))
	UTextBlock* Text_Message;
public:
	void SetMessage(FText text);
};
