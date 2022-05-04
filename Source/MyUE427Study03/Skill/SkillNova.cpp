// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillNova.h"

#include "Kismet/GameplayStatics.h"
#include "MyUE427Study03/Characters/CharacterBase.h"

void ASkillNova::OnSkillNotify()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particleSystem,
	                                         playerReference->GetMesh()->GetSocketLocation("foot_l"), playerReference->GetActorRotation());
}
