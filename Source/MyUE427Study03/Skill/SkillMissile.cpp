// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillMissile.h"

#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/Enemies/EnemyNormal.h"

// Sets default values
ASkillMissile::ASkillMissile(): ASkillBase()
{
}

bool ASkillMissile::IsInAttackRange()
{
	return (playerReference->GetDistanceTo(playerReference->selectEnemy) <= GetCurrentStage().range);
}

void ASkillMissile::OnTryCastSpell()
{
	Super::OnTryCastSpell();
}

void ASkillMissile::InitSpellCast()
{
	Super::InitSpellCast();
}

void ASkillMissile::OnSpellCast()
{
	Super::OnSpellCast();
}

void ASkillMissile::OnSkillNotify()
{
	Super::OnSkillNotify();
}

void ASkillMissile::MoveToEnemy()
{
}
