// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SkillTree_Category.h"

#include "UI_SkillTree_MainTree.h"

void UUI_SkillTree_Category::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Category->OnHovered.AddDynamic(this, &UUI_SkillTree_Category::OnCategoryButtonHovered);
	Button_Category->OnUnhovered.AddDynamic(this, &UUI_SkillTree_Category::OnCategoryButtonUnhovered);
	Button_Category->OnClicked.AddDynamic(this, &UUI_SkillTree_Category::OnCategoryButtonClicked);
}

void UUI_SkillTree_Category::OnCategoryButtonHovered()
{
	Text_CategoryName->SetColorAndOpacity(FLinearColor(0.83f, 0.83f, 0.83f, 1.0f));
}

void UUI_SkillTree_Category::OnCategoryButtonUnhovered()
{
	if (!bSelected)
	{
		Text_CategoryName->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f, 1.0f));
	}
}

void UUI_SkillTree_Category::OnCategoryButtonClicked()
{
	mainTreeRef->OnCategoryClicked(index);
}

void UUI_SkillTree_Category::ChangeState(bool isSelected)
{
	if (isSelected != bSelected)
	{
		bSelected = isSelected;
		Text_CategoryName->SetColorAndOpacity(isSelected ? FLinearColor::White : FLinearColor::Gray);
		Button_Category->SetIsEnabled(!isSelected);
	}
}
