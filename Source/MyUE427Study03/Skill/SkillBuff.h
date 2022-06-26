// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "MyUE427Study03/UserWidget/UI_BuffWidget.h"
#include "SkillBuff.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API ASkillBuff : public ASkillBase
{
	GENERATED_BODY()

public:
	const float K_DELTA_TIME = 0.01f;
	
	UUI_BuffWidget* buffWidgetRef;

	UPROPERTY(EditAnywhere)
	UTexture2D* buffIcon;

	//buf持续的时间
	float buffDuration;

	float remainingTime;

private:
	FTimerHandle timerHandle_UpdateEffect;
	
public:
	//Buff效果施加
	virtual void ApplyEffect(float deltaTime);

	//Buff移除
	virtual void RemoveEffect();

	//Buff重置
	virtual void RestBuff();

	//Buff激活, 技能的入口
	virtual void OnActive();

	virtual void OnDeActive();

	//定时器
	virtual void OnUpdateBuff();

	virtual void OnSkillNotify() override;
};
