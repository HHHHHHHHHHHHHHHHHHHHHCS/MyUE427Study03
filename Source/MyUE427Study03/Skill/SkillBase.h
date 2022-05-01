// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillInfo.h"
#include "GameFramework/Actor.h"
#include "SkillBase.generated.h"


UCLASS()
class MYUE427STUDY03_API ASkillBase : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Skill Info")
	FSkillInfo skillInfo;

	int currentStageIndex;

private:
	bool bIsCooldown; //是否在冷却
	bool bCurrCasting; //是否正在释放

	float currCD; //当前的CD
	FTimerHandle timerHandle_cooldown;

	class UUI_SkillHotkey* hotkey; //技能绑定的快捷键
	class ACharacterBase* playerReference; //谁释放了该技能

public:
	// Sets default values for this actor's properties
	ASkillBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE FSkillStage GetCurrentStage()
	{
		return skillInfo.stages[currentStageIndex];
	}

	FORCEINLINE void SetHotkey(UUI_SkillHotkey* _hotkey)
	{
		hotkey = _hotkey;
	}

	FORCEINLINE bool IsCooldown() const
	{
		return bIsCooldown;
	}

	FORCEINLINE bool CurrCasted() const
	{
		return bCurrCasting;
	}

	UFUNCTION(BlueprintCallable)
	void OnTryCastSpell();

	FORCEINLINE ACharacterBase* GetPlayerRef() const
	{
		return playerReference;
	}

	FORCEINLINE void SetPlayerRef(ACharacterBase* player)
	{
		this->playerReference = player;
	}

	//初始释放, 用来做条件判断, 比如说魔法值
	void InitSpellCast();

	void OnSpellCast();

	void OnCastCompleted();

	//技能冷却
	void OnCooldown();

	//技能冷却结束
	void OnCooldownExpired();
};
