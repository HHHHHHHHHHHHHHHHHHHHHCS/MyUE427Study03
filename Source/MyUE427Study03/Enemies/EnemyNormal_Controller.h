// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyNormal_Controller.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API AEnemyNormal_Controller : public AAIController
{
	GENERATED_BODY()
public:
	class UNavigationSystemV1* navSys;

	class AEnemyNormal* enemyPawn;

	//巡逻的移动速度
	float patrolWalkSpeed = 200.0f;

	//追逐的移动速度
	float aggroedWalkSpeed = 400.0f;

	//攻击范围
	float attackRange = 300.0f;

	//攻击动画蒙太奇列表
	TArray<UAnimMontage*> attackAnimMontages;

protected:
	//初始的位置
	FVector startLocation;

	FTimerHandle timerHandle_patrol;

	//是否处于追逐状态
	bool bIsPatrolling = true;

	//追逐的目标
	AActor* targetActor;

	//是否是追逐目标, 但是目标脱离了的状态
	bool bisRunningBack;

	//当前正在播放的攻击动画
	UAnimMontage* currAttackMontage;

	//当前的动画索引
	int currAttackIndex = 0;



public:
	AEnemyNormal_Controller();

	virtual void OnPossess(APawn* InPawn) override;

	void Patrol();

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void DetectedPool();

	//得到要播放的下一个动画索引, 如果动画数组到头则重置为0
	int GetNextAnimationIndex();

	//目标是否在攻击范围内
	bool GetIsInAttackRange();
};
