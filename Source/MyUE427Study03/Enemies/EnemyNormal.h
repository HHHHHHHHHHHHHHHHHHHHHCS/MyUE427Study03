// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "MyUE427Study03/Interface/DamageableInterface.h"
#include "MyUE427Study03/Interface/SelectableInterface.h"
#include "MyUE427Study03/Skill/SkillEnum.h"
#include "MyUE427Study03/UserWidget/UI_EnemyInfoWidget.h"
#include "EnemyNormal.generated.h"

class AElementBase;
UCLASS()
class MYUE427STUDY03_API AEnemyNormal : public ACharacter, public IDamageableInterface, public ISelectableInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Enemy")
	FText enemyName = FText::FromString("Spider");

	UPROPERTY(EditAnywhere, Category="Enemy")
	int level = 1;

	UPROPERTY(EditAnywhere, Category="Enemy")
	float baseDamage = 25.0f;

	UPROPERTY(EditAnywhere, Category="Enemy")
	EAttackDamageType attackDamageType = EAttackDamageType::Physical;

	UPROPERTY(EditAnywhere, Category="Enemy")
	TSubclassOf<AElementBase> element;

	UPROPERTY(EditAnywhere, Category="Enemy")
	int critChance = 25;

	UPROPERTY(EditAnywhere, Category="Enemy")
	float totalHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category="Enemy")
	float expForKill = 25.0f;

	UPROPERTY(EditAnywhere, Category="Enemy")
	float respawnTime = 10.0f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Behavior")
	bool bIsDead;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Behavior")
	bool bDoesRespawn = true;

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

	UPROPERTY(EditAnywhere, Category="UI")
	UWidgetComponent* enemyWidgetComponent;

	UPROPERTY(EditAnywhere, Category="UI")
	USphereComponent* showUICollision;

	UPROPERTY(EditAnywhere, Category="UI")
	bool bInShowUIRange;

	UPROPERTY(VisibleAnywhere, Category="Hit")
	UArrowComponent* hitArrow;

	//初始的位置
	FVector startLocation;


protected:
	class AEnemyNormal_Controller* myController;

	UUI_EnemyInfoWidget* enemyInfoWidget;

	float currentHealth;

	FTimerHandle timerHandle_Respawn;

	bool bSelected = false;

	ACharacterBase* mainPlayer;


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

	UFUNCTION(BlueprintCallable)
	void Notify_AttackHit();

	void AttackRay();

	void InitWidget();

	UFUNCTION()
	void OnBeginOverlap_ShowUI(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                           const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap_ShowUI(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void UpdateHealthBar();

	void ResetHealth();

	virtual void ChangeHealth(float damage);

	virtual void OnReceiveDamage(float baseDamage, int attackerCritChance, EAttackDamageType type,
	                             TSubclassOf<class AElementBase> attackElement, AActor* attacker,
	                             class ASkillBase* skill) override;

	virtual void OnDeath(AActor* killer);

	virtual void OnRespawn();

	//选中
	virtual void OnSelected(class ACharacterBase* character) override;
	//离开选中
	virtual void OnSelectionEnd(class ACharacterBase* character) override;
};
