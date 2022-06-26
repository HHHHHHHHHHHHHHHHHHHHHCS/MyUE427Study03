// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBuff.h"
#include "SkillBuff_Health.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API ASkillBuff_Health : public ASkillBuff
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect(float deltaTime) override;
};
