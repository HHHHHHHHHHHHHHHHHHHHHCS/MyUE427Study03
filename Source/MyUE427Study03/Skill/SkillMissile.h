// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "GameFramework/Actor.h"
#include "SkillMissile.generated.h"

UCLASS()
class MYUE427STUDY03_API ASkillMissile : public ASkillBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category=Effect)
	UParticleSystem* missileEffect; //发射子弹所持有的特效

	UPROPERTY(EditAnywhere, Category=Effect)
	UParticleSystem* impactEffect; //子弹打到目标播放的特效

	UPROPERTY(EditAnywhere, Category=Skill)
	TSubclassOf<class AMagicProjectile> magicProjectile;

public:
	// Sets default values for this actor's properties
	ASkillMissile();

	bool IsInAttackRange();

	virtual void OnTryCastSpell() override;

	virtual void InitSpellCast() override;

	virtual void OnSpellCast() override;

	virtual void OnSkillNotify() override;

	virtual void MoveToEnemy();
};
