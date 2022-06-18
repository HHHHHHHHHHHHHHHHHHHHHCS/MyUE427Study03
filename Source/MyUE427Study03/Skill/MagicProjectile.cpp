// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicProjectile.h"

#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/Enemies/EnemyNormal.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/ArrowComponent.h"


// Sets default values
AMagicProjectile::AMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SetRootComponent(sphereCollisionComp);

	particleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	particleSystemComp->SetupAttachment(GetRootComponent());

	projectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	projectileMoveComp->ProjectileGravityScale = 0;
	projectileMoveComp->Velocity = FVector::ZeroVector;
	projectileMoveComp->bIsHomingProjectile = true;
}

// Called when the game starts or when spawned
void AMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	skill = Cast<ASkillMissile>(GetOwner());
	missileEffect = skill->missileEffect;
	impatctEffect = skill->impactEffect;
	particleSystemComp->SetTemplate(missileEffect);
	// projectileMoveComp->InitialSpeed = skill->GetCurrentStage().missileSpeed;
	projectileMoveComp->HomingTargetComponent =skill->GetPlayerRef()->selectEnemy->hitArrow;
	projectileMoveComp->HomingAccelerationMagnitude = skill->GetCurrentStage().missileSpeed;
}

// Called every frame
void AMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
