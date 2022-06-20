// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillMissile.h"

#include "MagicProjectile.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
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
	if (playerReference->selectEnemy)
	{
		Super::OnTryCastSpell();
	}
}

void ASkillMissile::InitSpellCast()
{
	if (IsInAttackRange())
	{
		StopCalcDist();
		Super::InitSpellCast();
	}
	else
	{
		GetWorldTimerManager().SetTimer(timerHandle_CalcDistToEnemy, this, &ASkillMissile::CalcDistToEnemy
		                                , 0.01f, true);
		playerReference->sKillMissile = this;
	}
}

void ASkillMissile::OnSpellCast()
{
	const FRotator rot = UKismetMathLibrary::FindLookAtRotation(playerReference->GetActorLocation(),
	                                                            playerReference->selectEnemy->GetActorLocation());
	playerReference->SetActorRotation(rot);
	Super::OnSpellCast();
}

void ASkillMissile::OnSkillNotify()
{
	FActorSpawnParameters params;
	params.Owner = this;
	GetWorld()->SpawnActor<AMagicProjectile>(magicProjectile
	                                         , playerReference->GetMesh()->GetSocketLocation("Muzzle_01")
	                                         , playerReference->GetMesh()->GetSocketRotation("Muzzle_01")
	                                         , params);
}

void ASkillMissile::CalcDistToEnemy()
{
	if (playerReference->selectEnemy)
	{
		if (IsInAttackRange())
		{
			InitSpellCast();
		}
		else
		{
			UAIBlueprintHelperLibrary::SimpleMoveToActor(playerReference->playerController
			                                             , playerReference->selectEnemy);
		}
	}
}

void ASkillMissile::StopCalcDist()
{
	GetWorldTimerManager().ClearTimer(timerHandle_CalcDistToEnemy);
	playerReference->sKillMissile = nullptr;
}
