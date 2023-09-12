// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UI_ItemHotKey.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_ItemHotKey : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UBorder* Border_Bg;

	UPROPERTY(meta=(BindWidget))
	UImage* Image_Icon;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* HBOX_Amount;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Amount;

public:
	bool isEmpty = true;
	int inventoryIndex; // 拖过来的物品在背包的哪个插槽上
	class AInventory* inventory;
	FLinearColor defaultTint = FLinearColor(0.86f, 0.86f, 0.86f, 1.0f);
	FLinearColor dragOverTint = FLinearColor(1.0f, 0.47f, 0.0f, 1.0f);
	bool isDragOver;

public :
	void UpdateInfo();

	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
