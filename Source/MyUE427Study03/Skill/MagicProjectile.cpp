// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicProjectile.h"

#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/Enemies/EnemyNormal.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


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
	projectileMoveComp->HomingTargetComponent = skill->GetPlayerRef()->selectEnemy->hitArrow;
	projectileMoveComp->HomingAccelerationMagnitude = skill->GetCurrentStage().missileSpeed;
	sphereCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMagicProjectile::OnBeginOverlap);
	// sphereCollisionComp->OnComponentEndOverlap.AddDynamic(this, &AMagicProjectile::OnEndOverlap);
}

// Called every frame
void AMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMagicProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	AEnemyNormal* tempEnemy = Cast<AEnemyNormal>(OtherActor);
	if (!tempEnemy || OtherComp != tempEnemy->GetCapsuleComponent())
	{
		return;
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), impatctEffect, SweepResult.ImpactPoint
	                                         , FRotator::ZeroRotator);
	FSkillStage stage = skill->GetCurrentStage();
	tempEnemy->OnReceiveDamage(stage.damage, stage.criticalChance, stage.damageType
	                           , skill->skillInfo.skillElement, skill->GetPlayerRef(), skill);
	Destroy();
}

// void AMagicProjectile::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
// {
// }
