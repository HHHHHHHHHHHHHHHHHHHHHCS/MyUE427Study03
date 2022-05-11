// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SkillHotkey.h"

#include "SkillDragOperation.h"
#include "UI_SkillDrag.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MyUE427Study03/Skill/SkillBase.h"

bool UUI_SkillHotkey::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	Button_Skill->OnClicked.AddDynamic(this, &UUI_SkillHotkey::OnSKillButtonClicked);
	cooldownMat = Image_Cooldown->GetDynamicMaterial();
	dragOverColor = FLinearColor(1.0f, 0.82f, 0.0f, 0.5f);
	defaultColor = FLinearColor(0, 0, 0, 0.2f);
	return true;
}

void UUI_SkillHotkey::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (!bHasSetKeyName)
	{
		bHasSetKeyName = true;
		Text_Hotkey->SetText(key.GetDisplayName());
	}
}

void UUI_SkillHotkey::SetAssignSpell(ASkillBase* newAssignedSpell)
{
	this->assignedSpell = newAssignedSpell;
	assignedSpell->SetHotkey(this);
	Button_Skill->SetIsEnabled(true);
	if (assignedSpell->GetCurrentStage().overrideIcon)
	{
		Image_SkillIcon->SetBrushFromTexture(assignedSpell->GetCurrentStage().overrideIcon);
	}
	else
	{
		Image_SkillIcon->SetBrushFromTexture(assignedSpell->skillInfo.icon);
	}
	Image_SkillIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UUI_SkillHotkey::ClearAssignedSpell()
{
	if (assignedSpell)
	{
		assignedSpell->SetHotkey(nullptr);
		assignedSpell = nullptr;

		Button_Skill->SetIsEnabled(false);
		Image_SkillIcon->SetBrushFromTexture(nullptr);
		Image_SkillIcon->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUI_SkillHotkey::OnSKillButtonClicked()
{
	assignedSpell->OnTryCastSpell();
}

void UUI_SkillHotkey::EnableHotkey()
{
	bIsActive = true;
	if (!assignedSpell->IsCooldown())
	{
		Button_Skill->SetIsEnabled(true);
		Image_SkillIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Image_Cooldown->SetVisibility(ESlateVisibility::Hidden);
		Image_SkillIcon->SetColorAndOpacity(FLinearColor::White);
	}
}

void UUI_SkillHotkey::DisableHotkey()
{
	bIsActive = false;
	if (assignedSpell->IsCooldown())
	{
		Button_Skill->SetIsEnabled(false);
		Image_SkillIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Image_Cooldown->SetVisibility(ESlateVisibility::Visible);
		cooldownMat->SetScalarParameterValue(FName("Percent"), 1.0f);
	}
}

void UUI_SkillHotkey::ResetStyle()
{
	bDraggedOver = false;
	Image_Bg->SetColorAndOpacity(defaultColor);
}

FReply UUI_SkillHotkey::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseButtonDown"));
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (!assignedSpell)
	{
		return FReply::Handled();
	}

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) && !assignedSpell->IsCooldown())
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::RightMouseButton).NativeReply;
	}

	return FReply::Handled();
}

void UUI_SkillHotkey::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	// UE_LOG(LogTemp, Warning, TEXT("NativeOnDragDetected"));
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	auto* cls = LoadClass<UUI_SkillDrag>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Skill/UI_SkillDrag.UI_SkillDrag_C'"));
	UUI_SkillDrag* skillDrag = CreateWidget<UUI_SkillDrag>(GetWorld(), cls);

	auto* icon = assignedSpell->GetCurrentStage().overrideIcon;
	if (!icon)
	{
		icon = assignedSpell->skillInfo.icon;
	}
	skillDrag->SetSkillIconTexture(icon);

	UDragDropOperation* tempOp = UWidgetBlueprintLibrary::CreateDragDropOperation(skillDragOperation);

	tempOp->DefaultDragVisual = skillDrag;
	OutOperation = tempOp;


	USkillDragOperation* skillDragOp = Cast<USkillDragOperation>(OutOperation);
	if (skillDragOp)
	{
		skillDragOp->skillActor = assignedSpell;
		skillDragOp->FromHotkey = this;
	}
}

bool UUI_SkillHotkey::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	// UE_LOG(LogTemp, Warning, TEXT("NativeOnDragOver"));
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	USkillDragOperation* dragOp = Cast<USkillDragOperation>(InOperation);

	if (!dragOp)
	{
		return false;
	}

	if (!bDraggedOver && dragOp->FromHotkey != this && !assignedSpell)
	{
		Image_Bg->SetColorAndOpacity(dragOverColor);
		bDraggedOver = true;
		return true;
	}
	return false;
}

void UUI_SkillHotkey::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	if (bDraggedOver)
	{
		USkillDragOperation* skillDragOp = Cast<USkillDragOperation>(InOperation);
		if (skillDragOp)
		{
			ResetStyle();
		}
	}
}

bool UUI_SkillHotkey::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	USkillDragOperation* skillDragOp = Cast<USkillDragOperation>(InOperation);

	if (skillDragOp)
	{
		if (skillDragOp->FromHotkey != this)
		{
			if (assignedSpell)
			{
				if (assignedSpell->IsCooldown())
				{
					return true;
				}
				else
				{
					auto tempAS = assignedSpell;
					ClearAssignedSpell();
					skillDragOp->FromHotkey->ClearAssignedSpell();
					SetAssignSpell(skillDragOp->skillActor);
					skillDragOp->FromHotkey->SetAssignSpell(tempAS);
					ResetStyle();
					return true;
				}
			}
			else
			{
				skillDragOp->FromHotkey->ClearAssignedSpell();
				SetAssignSpell(skillDragOp->skillActor);
				return true;
			}
		}
	}

	return false;
}
