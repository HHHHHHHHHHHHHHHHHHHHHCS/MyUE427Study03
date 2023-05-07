// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UI_ItemObtain.generated.h"

class UUserWidget_Main;
/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_ItemObtain : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_X;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Obtain;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Amount;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Name;

	UPROPERTY(meta=(BindWidget))
	UImage* Image_Icon;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float visibleDuration = 2.0f;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget_Main* mainUI;
public:
	void OnInit(TSubclassOf<class AItemBase> itemCls,int amount, UUserWidget_Main* mainUIWidget);
};
