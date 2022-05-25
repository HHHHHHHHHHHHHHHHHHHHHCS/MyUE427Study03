// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticLibrary.h"

float UStaticLibrary::CalculateFinalDamage(float baseDamage, int critChance, TSubclassOf<AElementBase> attackerElement
                                           , TSubclassOf<AElementBase> defenderElement)
{
	float currDamage = baseDamage * FMath::RandRange(0.9f, 1.1f);

	EEffectiveness localEffectiveness;
	if (attackerElement && defenderElement)
	{
		if (defenderElement->GetDefaultObject<AElementBase>()->skillElementInfo.weakness.Contains(attackerElement))
		{
			localEffectiveness = EEffectiveness::LowEffective;
		}
		else if (defenderElement->GetDefaultObject<AElementBase>()->skillElementInfo.enhance.Contains(attackerElement))
		{
			localEffectiveness = EEffectiveness::SuperEffective;
		}
		else
		{
			localEffectiveness = EEffectiveness::Effective;
		}
	}
	else
	{
		localEffectiveness = EEffectiveness::Effective;
	}

	switch (localEffectiveness)
	{
	case EEffectiveness::Effective:
		break;
	case EEffectiveness::SuperEffective:
		currDamage *= 1.5f;
		break;
	case EEffectiveness::LowEffective:
		currDamage *= 0.5f;
		break;
	}

	//[0:101)->[0:100]
	if (FMath::RandHelper(101) <= critChance)
	{
		currDamage *= 2.0f;
	}

	return currDamage;
}
