// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageArea.h"

#include "Kismet/GameplayStatics.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ADamageArea::ADamageArea()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	particleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComp"));
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	SetRootComponent(boxComp);
	particleSystemComp->SetupAttachment(GetRootComponent());

	enableTimer = false;
	damageVal = 5.0f;
}

// Called when the game starts or when spawned
void ADamageArea::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ADamageArea::OnBeginOverlap);
	boxComp->OnComponentEndOverlap.AddDynamic(this, &ADamageArea::OnEndOverlap);
}

void ADamageArea::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacterBase* actor = Cast<ACharacterBase>(OtherActor);
	if (actor == nullptr)
	{
		return;
	}
	player = actor;
	ApplyAreaDamage();
	enableTimer = true;
	takeDamageTimer = 1.0f;
}

void ADamageArea::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacterBase* actor = Cast<ACharacterBase>(OtherActor);
	if (actor == nullptr)
	{
		return;
	}
	player = nullptr;
	enableTimer = false;
}

void ADamageArea::ApplyAreaDamage()
{
	UGameplayStatics::ApplyDamage(player, damageVal, nullptr, this, nullptr);
}

// Called every frame
void ADamageArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!enableTimer)
	{
		return;
	}
	takeDamageTimer -= DeltaTime;
	if (takeDamageTimer <= 0.0)
	{
		takeDamageTimer += 1.0f;
		ApplyAreaDamage();
	}
}
