// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_DragItem.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_DragItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	class UImage* Image_Icon;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_Amount;

public:
	void OnInit(int amount, UTexture2D* icon);
};
