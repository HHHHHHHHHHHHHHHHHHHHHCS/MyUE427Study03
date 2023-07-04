// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI_CraftItem.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_CraftItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Selected;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Name;

	UPROPERTY(EditAnywhere, Category="Item")
	TSubclassOf<class AItemBase> item;

public:
	class UUI_CraftMenu* craftMenu;

public:
	virtual void NativeConstruct() override;
	
	void OnInit(TSubclassOf<class AItemBase> _item, class UUI_CraftMenu* _craftMenu);

	UFUNCTION()
	void Click_Selected();
};
