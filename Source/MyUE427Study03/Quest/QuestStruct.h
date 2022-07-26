// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestEnum.h"
#include "UObject/NoExportTypes.h"
#include "QuestStruct.generated.h"

//任务完成之后的奖励
USTRUCT()
struct FQuestReward
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="QuestInfo")
	int experience;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	int coin;
};

//目标的位置
USTRUCT()
struct FGlobalLocation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="QuestInfo")
	bool bHasLocation;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	FVector location;
};

USTRUCT()
struct FGoalInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="QuestInfo")
	EGoalTypes type = EGoalTypes::Custom;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	bool bCustomGoal;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	FText goalText; // 任务的记录描述

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	int aAmountToHunt; //要杀死的怪物数量

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	bool bUpdateQuestDesc; //当前任务完成, 会有下一个任务的更新提示

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	bool bUpdateDesc; //任务结束

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	TArray<int> followingSubGoalIndices; //当前任务完成之后接下来的任务索引
};

USTRUCT()
struct FQuestInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="QuestInfo")
	FText name;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	EQuestCategories category;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	FText desc;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	ERegions region;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	FQuestReward completionReward;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	int suggestedLevel;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	int difficulty;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	TArray<FGoalInfo> subGoals;
};

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UQuestStruct : public UObject
{
	GENERATED_BODY()
};
