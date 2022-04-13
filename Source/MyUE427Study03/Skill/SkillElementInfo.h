// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillElementInfo.generated.h"

class ASkillElementBase;

//元素的信息
USTRUCT()
struct FSkillElementInfo
{
	GENERATED_USTRUCT_BODY()

public:
	
	UPROPERTY(EditAnywhere,Category="SkillElement")
	FText name;
	UPROPERTY(EditAnywhere,Category="SkillElement")
	UTexture2D* icon; //元素图标
	UPROPERTY(EditAnywhere,Category="SkillElement")
	FLinearColor color; //元素的颜色
	UPROPERTY(EditAnywhere,Category="SkillElement")
	TArray<TSubclassOf<ASkillElementBase>> resistances; //增强效果的元素
	UPROPERTY(EditAnywhere,Category="SkillElement")
	TArray<TSubclassOf<ASkillElementBase>> weakness; //虚弱效果的元素
};
