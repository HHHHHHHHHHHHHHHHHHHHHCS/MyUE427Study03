// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SkillTree_MainTree.h"

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
