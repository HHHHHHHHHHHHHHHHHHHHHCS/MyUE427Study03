// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "UI_SkillTree_Connection.generated.h"

/**
 * 用来连接两个技能的连线
 */
UCLASS()
class MYUE427STUDY03_API UUI_SkillTree_Connection : public UUserWidget
{
	GENERATED_BODY()

public:
	//连线, 当没有学习前置技能的时候Alpha值为0.2
	//学习之后,Alpha值为0.7
	UPROPERTY(Meta=(BindWidget))
	UImage* Image_Line;

	bool bActive;

	TSubclassOf<class ASkillBase> forSKill;

	void Active();
};
