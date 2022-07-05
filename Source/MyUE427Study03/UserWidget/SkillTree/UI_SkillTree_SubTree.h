// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "UI_SkillTree_SubTree.generated.h"

/**
 * 与种类相对应的下面的界面
 */
UCLASS()
class MYUE427STUDY03_API UUI_SkillTree_SubTree : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* CanvasPanel_Root;
};
