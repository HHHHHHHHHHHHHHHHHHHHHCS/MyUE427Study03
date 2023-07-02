// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUE427Study03/InventorySystem/InventoryStruct.h"
#include "UI_CraftMenu.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_CraftMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	class UButton* Button_Close;

	UPROPERTY(meta=(BindWidget))
	class UScrollBox* ScrollBox_CraftItems;

	UPROPERTY(meta=(BindWidget))
	class UButton* Button_Craft;

	UPROPERTY(meta=(BindWidget))
	class UImage* Image_Icon;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text_Desc;

	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* VBox_RecipeEntryList;

	UPROPERTY(meta=(BindWidget))
	class UBorder* Border_Detail;

public:
	class AInventory* inventory;

	class UUI_CraftItem* currentCraft;

	TSubclassOf<AItemBase> currentItem;

	FItemInfo currentItemInfo;

	TArray<class UUI_RecipeEntry*> recipeEntries;

public:
	virtual void NativeConstruct() override;
	
	void Click_OnCraft(class UUI_CraftItem* widget);

	UFUNCTION()
	void Click_OnClose();

	UFUNCTION()
	void Click_OnCraft();
	
	void GenerateCraftItemList();

	void GenerateRecipeEntries();

	bool CanBeCrafted();

	void UpdateDetailWindow(TSubclassOf<class AItemBase> item);

	void InitCraftMenu(class AInventory* _inventory);
};
