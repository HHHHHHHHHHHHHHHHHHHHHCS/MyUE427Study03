// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SkillTree_MainTree.h"

#include "MyUE427Study03/Characters/CharacterBase.h"

void UUI_SkillTree_MainTree::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Close->OnClicked.AddDynamic(this, &UUI_SkillTree_MainTree::OnClosedButtonClicked);
}

void UUI_SkillTree_MainTree::OnCategoryClicked(int index)
{
	if (currSelectedIndex != index)
	{
		if (currSelectedIndex == -1)
		{
			Switcher_SubTree->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			currSelectedIndex = index;
			categoryUI[currSelectedIndex]->ChangeState(true);
			Switcher_SubTree->SetActiveWidgetIndex(currSelectedIndex);
		}
		else
		{
			categoryUI[currSelectedIndex]->ChangeState(false);
			currSelectedIndex = index;
			categoryUI[currSelectedIndex]->ChangeState(true);
			Switcher_SubTree->SetActiveWidgetIndex(currSelectedIndex);
		}
	}
}

void UUI_SkillTree_MainTree::OnClosedButtonClicked()
{
	skillTreeComp->HandleShowCommand();
}

void UUI_SkillTree_MainTree::UpdateLevel()
{
	Text_Lv->SetText(FText::AsNumber(skillTreeComp->playerCharacter->GetCurrentLevel()));
}

void UUI_SkillTree_MainTree::UpdateSP()
{
	Text_Sp->SetText(FText::AsNumber(skillTreeComp->skillPoints));
}

void UUI_SkillTree_MainTree::GenerateCategories()
{
	SBox_Categories->ClearChildren();
	Switcher_SubTree->ClearChildren();

	categoryUI.Empty();
	subTreeWidgets.Empty();

	auto categoryCls = LoadClass<UUI_SkillTree_Category>(
		GetWorld(), TEXT(
			"WidgetBlueprint'/Game/Blueprints/UserWidget/Skill/SkillTree/UI_SkillTree_Category.UI_SkillTree_Category_C'"));

	auto subTreeCls = LoadClass<UUI_SkillTree_SubTree>(
		GetWorld(), TEXT(
			"WidgetBlueprint'/Game/Blueprints/UserWidget/Skill/SkillTree/UI_SkillTree_SubTree.UI_SkillTree_SubTree_C'"));

	for (int i = 0; i < categoryData.Num(); i++)
	{
		const auto data = &categoryData[i];

		UUI_SkillTree_Category* category = CreateWidget<UUI_SkillTree_Category>(GetWorld(), categoryCls);
		category->categoryName = data->name;
		category->index = i;
		category->mainTreeRef = this;
		categoryUI.Add(category);
		SBox_Categories->AddChild(category);

		UUI_SkillTree_SubTree* subTree = CreateWidget<UUI_SkillTree_SubTree>(GetWorld(), subTreeCls);
		subTree->content = data->content;
		subTree->mainTreeRef = this;
		subTreeWidgets.Add(subTree);
		Switcher_SubTree->AddChild(subTree);
	}
}
