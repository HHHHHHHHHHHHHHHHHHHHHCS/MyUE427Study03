// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "UI_SkillDrag.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_SkillDrag : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UImage* Image_SkillIcon;

public:
	void SetSkillIconTexture(UTexture2D* texture);
};
