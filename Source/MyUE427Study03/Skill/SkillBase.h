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

	UPROPERTY(EditAnywhere, Category="Skill Info")
	UAnimMontage* skillAnimMontage;

	int currentStageIndex = -1;

protected:
	bool bIsCooldown; //是否在冷却
	bool bCurrCasting; //是否正在释放

	float currCD; //当前的CD
	FTimerHandle timerHandle_cooldown;

	class UUI_SkillHotkey* hotkey; //技能绑定的快捷键
	class ACharacterBase* playerReference; //谁释放了该技能
	UAnimInstance* animInst;

	FTimerHandle TimerHandle_ResetMove;

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
		return skillInfo.stages[FMath::Clamp(currentStageIndex, 0, skillInfo.stages.Num() - 1)];
	}

	FORCEINLINE FSkillStage GetNextStage()
	{
		return skillInfo.stages[FMath::Clamp(currentStageIndex + 1, 0, skillInfo.stages.Num() - 1)];
	}

	FORCEINLINE int GetCurrentStageIndex()
	{
		return currentStageIndex;
	}

	FORCEINLINE void InCreaseCurrentStageIndex(int val = 1)
	{
		currentStageIndex = FMath::Min(currentStageIndex + val, skillInfo.stages.Num() - 1);
	}

	FORCEINLINE void DeCreaseCurrentStageIndex(int val = 1)
	{
		currentStageIndex = FMath::Max(currentStageIndex - val, -1);
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
	virtual void OnTryCastSpell();


	FORCEINLINE void SetPlayerRef(ACharacterBase* player)
	{
		playerReference = player;
	}

	FORCEINLINE ACharacterBase* GetPlayerRef() const
	{
		return playerReference;
	}

	//初始释放, 用来做条件判断, 比如说魔法值
	virtual void InitSpellCast();

	virtual void OnSpellCast();

	virtual void OnCastCompleted();

	//技能冷却
	virtual void OnCooldown();

	//技能冷却结束
	void OnCooldownExpired();

	//播放技能动画
	virtual void PlaySkillAnim(UAnimMontage* skillAnimMon);

	void ResetMovement();

	UFUNCTION(BlueprintCallable)
	virtual void OnSkillNotify();
};
