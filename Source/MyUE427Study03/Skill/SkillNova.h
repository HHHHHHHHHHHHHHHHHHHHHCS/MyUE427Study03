// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "SkillNova.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API ASkillNova : public ASkillBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,Category="Particle")
	UParticleSystem* particleSystem;

public:
	void OnSkillNotify() override;
};
