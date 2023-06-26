// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_CraftMenu.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_CraftMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	class UButton* Button_Close;

	UPROPERTY(meta=(BindWidget))
	class UScrollBox* ScrollBox_CraftItems;

	UPROPERTY(meta=(BindWidget))
	class UButton* Button_Craft;

	UPROPERTY(meta=(BindWidget))
	class UImage* Image_Icon;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_Desc;

	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* VBox_RecipeEntryList;
};
