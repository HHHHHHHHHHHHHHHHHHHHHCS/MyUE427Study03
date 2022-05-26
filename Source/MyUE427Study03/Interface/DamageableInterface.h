// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUE427Study03/Skill/SkillEnum.h"
#include "DamageableInterface.generated.h"

/**
 * 
 */
UINTERFACE()
class UDamageableInterface : public UInterface
{
	GENERATED_BODY()
};

class IDamageableInterface
{
	GENERATED_BODY()
public:
	virtual void OnReceiveDamage(float baseDamage, int critChance, EAttackDamageType type,
	                             TSubclassOf<class AElementBase> attackElement, AActor* attacker, class ASkillBase* skill) = 0;
};
