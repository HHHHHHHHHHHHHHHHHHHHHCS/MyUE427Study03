// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "UI_SkillTree_Entry.generated.h"

/**
 * 技能插槽图标
 */
UCLASS()
class MYUE427STUDY03_API UUI_SkillTree_Entry : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(Meta=(BindWidget))
	UOverlay* Overlay_Skill;

	UPROPERTY(Meta=(BindWidget))
	UImage* Image_SkillIcon;

	UPROPERTY(Meta=(BindWidget))
	UImage* Image_SkillBorder;

	UPROPERTY(Meta=(BindWidget))
	UTextBlock* Text_Stage;

	UPROPERTY(Meta=(BindWidget))
	UVerticalBox* VBOX_Upgrade;

	UPROPERTY(Meta=(BindWidget))
	UButton* Button_Plus;

	UPROPERTY(Meta=(BindWidget))
	UButton* Button_Minus;

	class UUI_SkillTree_SubTree* subTree;
	class ASkillBase* skillActor;
	TSubclassOf<ASkillBase> skillClass;
	bool bSpellLearned;


public :
	virtual void NativeConstruct() override;
	
	int GetAmountOfStages();
	void UpdateStageText();
	void UpdateIcon();
	void UpdateUpgradeBox();
	void OnSpellLearned();

	UFUNCTION()
	void OnPlusButtonClicked();
	
	UFUNCTION()
	void OnMinusButtonClicked();
};
