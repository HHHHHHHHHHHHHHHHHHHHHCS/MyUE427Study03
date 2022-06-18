// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillMissile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MagicProjectile.generated.h"

UCLASS()
class MYUE427STUDY03_API AMagicProjectile : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category="Skill")
	USphereComponent* sphereCollisionComp;

	UPROPERTY(VisibleAnywhere, Category="Skill")
	UParticleSystemComponent* particleSystemComp;

	UPROPERTY(VisibleAnywhere, Category="Skill")
	UProjectileMovementComponent* projectileMoveComp;

	UPROPERTY(VisibleAnywhere, Category="Skill")
	UParticleSystem* missileEffect;

	UPROPERTY(VisibleAnywhere, Category="Skill")
	UParticleSystem* impatctEffect;

	ASkillMissile* skill;

public:
	// Sets default values for this actor's properties
	AMagicProjectile();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
