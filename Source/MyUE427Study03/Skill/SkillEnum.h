// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillEnum.generated.h"

//技能作用的对象
UENUM()
enum class ETargetTypes : uint8
{
	Self,
	SelectedEnemy,
	SelectedArea,//AOE
	AreaAroundSelf, //自身周围
	Missile, //比如子弹,元气弹
};

//伤害的类型
UENUM()
enum class ESkillDamageType: uint8
{
	Physical,
	Magic,
	Real,
};

//效果, 比如带buff, 效果增加和效果削弱
UENUM()
enum class EEffectiveness: uint8
{
	Effective,
	SuperEffective,
	NoEffect,
};

UCLASS()
class MYUE427STUDY03_API USkillEnum : public UObject
{
	GENERATED_BODY()
};
