// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SkillTree_Entry.h"

#include "UI_SkillTree_MainTree.h"
#include "UI_SkillTree_SubTree.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MyUE427Study03/Skill/SkillBase.h"
#include "MyUE427Study03/UserWidget/SkillDragOperation.h"
#include "MyUE427Study03/UserWidget/UI_SkillDrag.h"

#define LOCTEXT_NAMESPACE "SkillTreeEntrySpace"

void UUI_SkillTree_Entry::NativeConstruct()
{
	Super::NativeConstruct();
	skillActor = GetWorld()->SpawnActor<ASkillBase>(skillClass, FVector::ZeroVector, FRotator::ZeroRotator);
	skillActor->SetPlayerRef(subTree->mainTreeRef->skillTreeComp->playerCharacter);
	UpdateStageText();
	UpdateIcon();
	UpdateUpgradeBox();
	Button_Plus->OnClicked.AddDynamic(this, &UUI_SkillTree_Entry::OnPlusButtonClicked);
	Button_Minus->OnClicked.AddDynamic(this, &UUI_SkillTree_Entry::OnMinusButtonClicked);
}

int UUI_SkillTree_Entry::GetAmountOfStages()
{
	return skillActor->skillInfo.stages.Num();
}

void UUI_SkillTree_Entry::UpdateStageText()
{
	Text_Stage->SetText(FText::Format(LOCTEXT("SkillTreeEntrySpace", "{0}/{1}")
	                                  , skillActor->currentStageIndex + 1, FText::AsNumber(GetAmountOfStages())));
}

void UUI_SkillTree_Entry::UpdateIcon()
{
	UTexture2D* tempTex;

	if (skillActor->GetCurrentStageIndex() < 0)
	{
		tempTex = skillActor->skillInfo.icon;
	}
	else
	{
		if (skillActor->GetCurrentStage().overrideIcon)
		{
			tempTex = skillActor->GetCurrentStage().overrideIcon;
		}
		else
		{
			tempTex = skillActor->skillInfo.icon;
		}
	}

	Image_SkillIcon->SetBrushFromTexture(tempTex);
}

void UUI_SkillTree_Entry::UpdateUpgradeBox()
{
	if (subTree->mainTreeRef->skillTreeComp->BCanUpgradeSpell(skillActor))
	{
		Button_Plus->SetVisibility(ESlateVisibility::Visible);
		Button_Minus->SetVisibility(ESlateVisibility::Hidden);
		VBOX_Upgrade->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		if (skillActor->GetCurrentStageIndex() >= 1)
		{
			Button_Minus->SetVisibility(ESlateVisibility::Visible);
		}
		SetColorAndOpacity(FLinearColor::White);
	}
	else
	{
		Button_Plus->SetVisibility(ESlateVisibility::Hidden);
		if (skillActor->GetCurrentStageIndex() >= 1)
		{
			Button_Minus->SetVisibility(ESlateVisibility::Visible);
			VBOX_Upgrade->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			SetColorAndOpacity(FLinearColor::White);
		}
		else
		{
			if (subTree->mainTreeRef->skillTreeComp->BPlayerLearnedSpell(skillClass))
			{
				SetColorAndOpacity(FLinearColor::White);
				VBOX_Upgrade->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.3f));
				VBOX_Upgrade->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void UUI_SkillTree_Entry::OnSpellLearned()
{
	bSpellLearned = true;
	Image_SkillIcon->SetColorAndOpacity(FLinearColor::White);
}

void UUI_SkillTree_Entry::OnPlusButtonClicked()
{
	subTree->mainTreeRef->skillTreeComp->UpgradeSpell(skillActor, this);
}

void UUI_SkillTree_Entry::OnMinusButtonClicked()
{
	subTree->mainTreeRef->skillTreeComp->DowngradeSpell(skillActor, this);
}

FReply UUI_SkillTree_Entry::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseButtonDown"));
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (bSpellLearned)
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::RightMouseButton).NativeReply;
	}

	return FReply::Handled();
}

void UUI_SkillTree_Entry::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                               UDragDropOperation*& OutOperation)
{
	// UE_LOG(LogTemp, Warning, TEXT("NativeOnDragDetected"));
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (subTree->mainTreeRef->skillTreeComp->BSkillOnHotkey(skillActor))
	{
		return;
	}

	auto* cls = LoadClass<UUI_SkillDrag>(
		GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Skill/UI_SkillDrag.UI_SkillDrag_C'"));

	UUI_SkillDrag* skillDrag = CreateWidget<UUI_SkillDrag>(GetWorld(), cls);

	auto* icon = skillActor->GetCurrentStage().overrideIcon;
	if (!icon)
	{
		icon = skillActor->skillInfo.icon;
	}
	skillDrag->SetSkillIconTexture(icon);

	UDragDropOperation* tempOp = UWidgetBlueprintLibrary::CreateDragDropOperation(skillDragOperation);

	tempOp->DefaultDragVisual = skillDrag;
	OutOperation = tempOp;


	USkillDragOperation* skillDragOp = Cast<USkillDragOperation>(OutOperation);
	if (skillDragOp)
	{
		skillDragOp->skillActor = skillActor;
		skillDragOp->FromHotkey = nullptr;
	}
}

#undef LOCTEXT_NAMESPACE
