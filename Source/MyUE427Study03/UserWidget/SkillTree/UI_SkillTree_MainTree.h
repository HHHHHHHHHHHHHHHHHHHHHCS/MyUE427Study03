// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_SkillTree_Category.h"
#include "UI_SkillTree_SubTree.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "MyUE427Study03/Components/SkillTreeComponent.h"
#include "UI_SkillTree_MainTree.generated.h"

/**
 * 技能书主容器
 */
UCLASS()
class MYUE427STUDY03_API UUI_SkillTree_MainTree : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta=(BindWidget))
	UTextBlock* Text_Sp;

	UPROPERTY(Meta=(BindWidget))
	UTextBlock* Text_Lv;

	UPROPERTY(Meta=(BindWidget))
	UButton* Button_Close;

	UPROPERTY(Meta=(BindWidget))
	UScrollBox* SBox_Categories;

	UPROPERTY(Meta=(BindWidget))
	UWidgetSwitcher* Switcher_SubTree;

	USkillTreeComponent* skillTreeComp;
	int currSelectedIndex = -1; // 当前选择的category所对应的index
	TArray<FSkillTreeCategory> categoryData; // category数据
	TArray<UUI_SkillTree_Category*> categoryUI; // 分类, 比如 skill, defense
	TArray<UUI_SkillTree_SubTree*> subTreeWidgets; // category对应的content

public:
	virtual void NativeConstruct() override;
	
	void OnCategoryClicked(int index);

	UFUNCTION()
	void OnClosedButtonClicked();
	
	void UpdateLevel();

	void UpdateSP();

	void GenerateCategories();
	
	void MyInitialize(USkillTreeComponent* treeComp);

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
