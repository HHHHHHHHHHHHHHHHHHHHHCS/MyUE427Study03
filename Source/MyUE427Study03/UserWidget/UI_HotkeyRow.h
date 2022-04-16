// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_SkillHotkey.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "UI_HotkeyRow.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUI_HotkeyRow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UHorizontalBox* RowBox; //存放着一排所创建的skillHotkey

	//这一排是我们所需要的按键, 是从外部传入的, 创建该hotkeyrow之后, 被赋值.
	TArray<FKey> keys;

	//是我们这一排拥有的skillHotKey
	TArray<UUI_SkillHotkey*> slotWidgets;

public:
	FORCEINLINE void SetHotkeys(TArray<FKey> _keys) { keys = _keys; }

	TArray<UUI_SkillHotkey> GenerateHotkeys();
};
