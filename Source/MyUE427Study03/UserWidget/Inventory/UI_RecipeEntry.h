// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UI_RecipeEntry.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_RecipeEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta=(BindWidget))
	UImage* Image_Icon;

	UPROPERTY(Meta=(BindWidget))
	UTextBlock* Text_Name;

public:
	TSubclassOf<class  AItemBase> item;
	class UUI_CraftMenu* craftMenu;
	int requiredAmount;
	int currentAmount;
	
public:
	void Update();
};
