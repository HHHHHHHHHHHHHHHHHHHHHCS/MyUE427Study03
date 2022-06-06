// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillNova.h"

#include "Kismet/GameplayStatics.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/Others/StaticLibrary.h"

void ASkillNova::OnSkillNotify()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particleSystem,
	                                         playerReference->GetMesh()->GetSocketLocation("foot_l"), playerReference->GetActorRotation());

	auto stage = GetCurrentStage();
	FCollisionShape sphereCollision = FCollisionShape::MakeSphere(stage.range);
	TArray<FHitResult> hitResults;
	bool isHit = GetWorld()->SweepMultiByChannel(hitResults, playerReference->GetActorLocation(), playerReference->GetActorLocation()
	                                             , FQuat::Identity, ECollisionChannel::ECC_Visibility, sphereCollision);
	if (isHit)
	{
		for (auto& item : hitResults)
		{
			if (UStaticLibrary::IsEnemy(item.GetActor()))
			{
				AEnemyNormal* enemy = Cast<AEnemyNormal>(item.Actor);
				enemy->OnReceiveDamage(stage.damage, stage.criticalChance, stage.damageType, skillInfo.skillElement, playerReference, this);
			}
		}
	}
}
