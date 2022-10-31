// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UI_Interaction.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_Interaction : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta=(BindWidget))
	UTextBlock* Text_Name;

public :
	void SetNameText(FText name);
};
