// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBuff_Health.h"

#include "MyUE427Study03/Characters/CharacterBase.h"

void ASkillBuff_Health::ApplyEffect(float deltaTime)
{
	playerReference->ChangeCurrentHP(5 * deltaTime);
}
