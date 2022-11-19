// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestStruct.h"
#include "GameFramework/Actor.h"
#include "QuestBase.generated.h"

UCLASS()
class MYUE427STUDY03_API
AQuestBase : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="QuestInfomation")
	FQuestInfo questInfo;

	UPROPERTY(EditAnywhere, Category="QuestInfomation")
	TArray<int> startingSubGoalIndices = {0}; // 初始的子任务, 有一个可能也有多个

	UPROPERTY(VisibleAnywhere, Category="QuestInfomation")
	TArray<FGoalInfo> completedSubGoals;
	
public:
	TArray<int> currentGoalIndices; // 当前的子任务索引

	TArray<FGoalInfo> currentGoals; // 当前的所有任务

	int selectedSubGoalIndex; //当前选择的要完成的任务索引

	int currentHuntedAmount; //当前杀死的怪物数量

public:
	// Sets default values for this actor's properties
	AQuestBase();

	void SetupStartingGoals();

	bool OnSubGoalCompleted(int subGoalIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateSubGoals();

	bool GoToNextSubGoal();

public:
	class UUI_Quest_Quest* questUI;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
