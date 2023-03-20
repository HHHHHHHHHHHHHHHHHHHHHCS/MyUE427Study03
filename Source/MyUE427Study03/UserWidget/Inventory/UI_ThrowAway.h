// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyUE427Study03/InventorySystem/InventoryStruct.h"
#include "UI_ThrowAway.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_ThrowAway : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta=(BindWidget))
	UImage* Image_ItemIcon;

	UPROPERTY(Meta=(BindWidget))
	UTextBlock* Text_Name;

	UPROPERTY(Meta=(BindWidget))
	UButton* Button_Minus;

	UPROPERTY(Meta=(BindWidget))
	UButton* Button_Plus;

	UPROPERTY(Meta=(BindWidget))
	UEditableTextBox* EText_Count;

	UPROPERTY(Meta=(BindWidget))
	UButton* Button_Confirm;

	UPROPERTY(Meta=(BindWidget))
	UButton* Button_Cancel;

public:
	int throwCount; //当前要丢弃的数量
	int maxAmount; //插槽的数量
	int currentIndex;
	class AInventory* inventoryRef;
	FItemInfo itemInfo;
	int clickCount;

private:
	FTimerHandle timerHandle_CountToZero;
	FTimerHandle timerHandle_Increase;
	FTimerHandle timerHandle_Decrease;

public:
	virtual void NativeConstruct() override;

	void UpdateInfo(int index);

	void IncreaseCount();

	void DecreaseCount();

	void ETextCountChange(const FText& Text);

	UFUNCTION()
	void OnButtonMinusClicked();

	UFUNCTION()
	void OnButtonPlusClicked();

	UFUNCTION()
	void OnMinusButtonPressed();

	UFUNCTION()
	void OnPlusButtonPressed();

	UFUNCTION()
	void OnMinusButtonReleased();

	UFUNCTION()
	void OnPlusButtonReleased();

	void SetClickCountToZero();
};
