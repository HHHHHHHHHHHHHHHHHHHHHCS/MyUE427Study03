// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InputCoreTypes.h"
#include "UI_SkillHotkey.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_SkillHotkey : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* Text_Hotkey;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* Text_Cooldown;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UImage* Image_SkillIcon;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UImage* Image_Bg;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UImage* Image_Cooldown;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* Button_Skill;

	bool bDraggedOver; //当前是否被拖拽
	FLinearColor dragOverColor; //这个插槽为空的时候有图标过来，显示的颜色
	FLinearColor defaultColor; //默认的颜色
	
	FKey key;

	class ASkillBase* assignedSpell; //分配的技能

	int hotkeyRow;
	int hotkeyIndex;

	UMaterialInstanceDynamic* cooldownMat;


private:
	bool bHasSetKeyName = false;

	bool bIsActive = false;

public:
	virtual bool Initialize() override;

	FORCEINLINE void SetKey(FKey _key) { this->key = _key; }

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//为技能分配快捷键
	void SetAssignSpell(ASkillBase* newAssignedSpell);

	//清除分配的技能
	void ClearAssignedSpell();

	UFUNCTION()
	void OnSKillButtonClicked();

	void EnableHotkey();

	void DisableHotkey();

	FORCEINLINE bool GetIsActive() const
	{
		return bIsActive;
	}

	//重设为初始的样子
	void ResetStyle();
};
