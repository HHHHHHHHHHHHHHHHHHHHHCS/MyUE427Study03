// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ElementBase.h"
#include "SkillEnum.h"
#include "SkillInfo.generated.h"


//技能的阶段(等级), 每一个等级的属性值不同
USTRUCT()
struct FSkillStage
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category="SkillData")
	int requiredLevel; //需要的前置等级

	UPROPERTY(EditAnywhere, Category="SkillData")
	TArray<TSubclassOf<class ASkillBase>> requiredSkills; //需要的前置技能

	UPROPERTY(EditAnywhere, Category="SkillData")
	UTexture2D* overrideIcon; //覆盖用的新图标, 如果为空则使用初始技能和的图标

	UPROPERTY(EditAnywhere, Category="SkillData")
	float range; //技能效果的范围

	UPROPERTY(EditAnywhere, Category="SkillData")
	float damage; //技能的伤害值

	UPROPERTY(EditAnywhere, Category="SkillData")
	EAttackDamageType damageType; //伤害的类型

	UPROPERTY(EditAnywhere, Category="SkillData")
	float criticalChance; //暴击率

	UPROPERTY(EditAnywhere, Category="SkillData")
	float cooldownTime; //技能的冷却时间

	UPROPERTY(EditAnywhere, Category="SkillData")
	float castingTime; //技能的释放的时间

	UPROPERTY(EditAnywhere, Category="SkillData")
	float manaCost; //魔法消耗值

	UPROPERTY(EditAnywhere, Category="SkillData")
	float missileSpeed; //投掷类速度
};

//技能的信息
USTRUCT()
struct FSkillInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category="SkillData")
	FText name;

	UPROPERTY(EditAnywhere, Category="SkillData")
	UTexture2D* icon;

	UPROPERTY(EditAnywhere, Category="SkillData")
	FText description; //技能的描述

	UPROPERTY(EditAnywhere, Category="SkillData")
	TSubclassOf<AElementBase> skillElement; //技能所属的信息

	UPROPERTY(EditAnywhere, Category="SkillData")
	ETargetTypes target; //做用对象

	UPROPERTY(EditAnywhere, Category="SkillData")
	TArray<FSkillStage> stages; //技能所拥有的所有阶段, 通过SkillInfo来获取
};
