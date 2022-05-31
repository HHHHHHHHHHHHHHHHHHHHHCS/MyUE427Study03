// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/Enemies/EnemyNormal.h"
#include "MyUE427Study03/Skill/SkillBase.h"
#include "MyUE427Study03/Skill/ElementBase.h"
#include "StaticLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UStaticLibrary : public UObject
{
	GENERATED_BODY()

public:
	static float CalculateFinalDamage(float baseDamage, int critChance
	                                  , TSubclassOf<AElementBase> attackerElement, TSubclassOf<AElementBase> defenderElement);

	FORCEINLINE static bool IsEnemy(AActor* actor)
	{
		return actor->GetClass() == AEnemyNormal::StaticClass()
			|| actor->GetClass()->IsChildOf(AEnemyNormal::StaticClass());
	}

	FORCEINLINE static bool TryGetPlayer(AActor* actor, ACharacterBase*& player)
	{
		player = Cast<ACharacterBase>(actor);
		return player != nullptr;
	}

	FORCEINLINE static bool IsPlayer(AActor* actor)
	{
		return actor->GetClass() == ACharacterBase::StaticClass()
			|| actor->GetClass()->IsChildOf(ACharacterBase::StaticClass());
	}
};
