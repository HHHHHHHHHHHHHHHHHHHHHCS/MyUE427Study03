// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "DamageArea.generated.h"

class ACharacterBase;
UCLASS()
class MYUE427STUDY03_API ADamageArea : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category="Component")
	UParticleSystemComponent* particleSystemComp;

	UPROPERTY(VisibleAnywhere, Category="Component")
	UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category="Component")
	float damageVal;
	
protected:
	ACharacterBase* player;
	bool enableTimer;
	float takeDamageTimer;

public:
	// Sets default values for this actor's properties
	ADamageArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ApplyAreaDamage();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
