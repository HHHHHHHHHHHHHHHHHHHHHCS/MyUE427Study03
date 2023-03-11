// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MyUE427Study03/InventorySystem/InventoryStruct.h"
#include "UI_InventoryActionMenu.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_InventoryActionMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UButton* Button_UseItem;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_ThrowAway;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_SplitStack;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Cancel;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_UseItem;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_ThrowAway;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_SplitStack;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Cancel;

public:
	class AInventory* inventoryRef;
	int currentIndex;
	FItemInfo itemInfo;
	int amount;
	
public:

	virtual void NativeConstruct() override;
	
	void UpdateInfo(int index);

	UFUNCTION()
	void OnButtonUseItemClick();

	UFUNCTION()
	void OnButtonThrowAwayClick();

	UFUNCTION()
	void OnButtonSplitStackClick();

	UFUNCTION()
	void OnButtonCancelClick();

};
