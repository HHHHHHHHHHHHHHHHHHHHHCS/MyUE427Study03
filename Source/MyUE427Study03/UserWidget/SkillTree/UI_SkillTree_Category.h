// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI_SkillTree_Category.generated.h"

/**
 * 技能树的种类, 包括技能,防御,buff
 */
UCLASS()
class MYUE427STUDY03_API UUI_SkillTree_Category : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta=(BindWidget))
	UButton* Button_Category;

	UPROPERTY(Meta=(BindWidget))
	UTextBlock* Text_CategoryName;
};
