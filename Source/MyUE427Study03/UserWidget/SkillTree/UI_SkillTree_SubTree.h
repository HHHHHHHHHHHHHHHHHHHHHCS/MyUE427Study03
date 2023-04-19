// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_SkillTree_Entry.h"
#include "UI_SkillTree_MainTree.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "MyUE427Study03/Skill/SkillTreeStruct.h"
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

	FSubTreeContent content;
	TArray<UUI_SkillTree_Entry*> skillEntries;
	TArray<class UUI_SkillTree_Connection*> connections;
	class UUI_SkillTree_MainTree* mainTreeRef;

public:
	virtual void NativeConstruct() override;
	
	void GenerateContent();
};
