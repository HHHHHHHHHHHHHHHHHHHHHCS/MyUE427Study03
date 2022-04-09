// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillEnum.generated.h"

UENUM()
enum class ETargetTypes : uint8
{
	Self,
	SelectedEnemy,
	SelectedArea,//AOE
	AreaAroundSelf, //自身周围
	Missile, //比如子弹,元气弹
};

UENUM()
enum class EDamageType: uint8
{
	Physical,
	Magic,
	Real,
};


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
