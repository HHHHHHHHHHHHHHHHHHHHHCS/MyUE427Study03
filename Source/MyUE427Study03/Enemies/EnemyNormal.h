// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyNormal.generated.h"

class ASkillElementBase;
UCLASS()
class MYUE427STUDY03_API AEnemyNormal : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Behavior")
	bool bIsDead;

	//是否是有侵略性的
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Behavior")
	bool bAggressive;

	UPROPERTY(VisibleAnywhere, Category="AI")
	class UAIPerceptionComponent* aiPerceptionComp;

	UPROPERTY(VisibleAnywhere, Category="AI")
	class UAISenseConfig_Sight* sightConfig;

	//攻击动画蒙太奇列表
	UPROPERTY(EditAnywhere, Category="Behavior")
	TArray<UAnimMontage*> attackAnimMontages;
	
	UPROPERTY(EditAnywhere, Category="Skill")
	TSubclassOf<ASkillElementBase> skillElement;
	
	//初始的位置
	FVector startLocation;


protected:
	class AEnemyNormal_Controller* myController;


public:
	// Sets default values for this character's properties
	AEnemyNormal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE bool GetIsDead() const
	{
		return bIsDead;
	}

	UFUNCTION()
	virtual void OnPerceptionUpdated(const TArray<AActor*>& updatedActors);
};
