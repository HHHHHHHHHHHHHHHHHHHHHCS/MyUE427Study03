// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "UI_Settings.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_Settings : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* Button_Save;
};
