// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Shop.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_Shop : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta=(BindWidget))
	class UButton* Button_Close;

	UPROPERTY(Meta=(BindWidget))
	class UUniformGridPanel* UGrid_OfferedItem;

	UPROPERTY(Meta=(BindWidget))
	class UTextBlock* Text_Coin;

	UPROPERTY(Meta=(BindWidget))
	class UUI_SellItem* UI_SellItem;

public:

	class ACharacterBase* playerChar;

	class ANPC_Merchant* merchant;

	TArray<class  UUI_OfferedItem*> offeredItemWidgets;

public:

	virtual void NativeConstruct() override;

	void UpdateCoin();

	void GenerateItemList();

	UFUNCTION()
	void Click_ButtonClose();
};
