// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_QuestCategory.h"

#include "Components/TextBlock.h"

void UUI_QuestCategory::NativeConstruct()
{
	Super::NativeConstruct();
	switch (currentStates)
	{
	case EQuestStates::CurrentQuest:
		SetCategoryName(FText::FromString("CurrentQuest"));
		break;
	case EQuestStates::CompletedQuest:
		SetCategoryName(FText::FromString("CompletedQuest"));
		break;
	case EQuestStates::FailedQuest:
		SetCategoryName(FText::FromString("FailedQuest"));
		break;
	default:
		break;
	}
	Button_Expand->OnClicked.AddDynamic(this, &UUI_QuestCategory::OnExpandButtonClicked);
}

void UUI_QuestCategory::SetCategoryName(FText text)
{
	Text_CategoryName->SetText(text);
}

void UUI_QuestCategory::OnExpandButtonClicked()
{
	bIsExpand = !bIsExpand;
	Button_Expand->SetRenderTransformAngle(bIsExpand ? 0 : -90);
	VBOX_QuestBox->SetVisibility(bIsExpand ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
}
