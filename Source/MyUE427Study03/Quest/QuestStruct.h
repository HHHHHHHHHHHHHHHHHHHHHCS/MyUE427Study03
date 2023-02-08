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
	int gold;
};

//目标的位置
USTRUCT()
struct FGoalLocation
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
	FText additionalName; //任务做用的目标

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	int amountToHunt; //要杀死的怪物数量

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	bool bUpdateQuestDesc; //当前任务完成, 会有下一个任务的更新提示

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	FGoalLocation goalLocation;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	FText updateDesc; //更新任务的描述

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	TArray<int> followingSubGoalIndices; //当前子任务完成之后接下来的子任务索引

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	bool useRadius;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	float radius;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	FLinearColor circleColor;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	TSubclassOf<class AActor> goalClass;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	int goalID;

	UPROPERTY(EditAnywhere, Category="QuestInfo")
	bool failMeansQuest;

	bool operator ==(const FGoalInfo& goalInfo) const
	{
		return (goalInfo.type == type)
			&& (goalInfo.bCustomGoal == bCustomGoal)
			&& (goalInfo.goalText.EqualTo(goalText))
			&& (goalInfo.additionalName.EqualTo(additionalName))
			&& (goalInfo.amountToHunt == amountToHunt)
			&& (goalInfo.goalLocation.bHasLocation == goalLocation.bHasLocation
				&& goalInfo.goalLocation.location == goalLocation.location)
			&& (goalInfo.bUpdateQuestDesc == bUpdateQuestDesc
				&& goalInfo.updateDesc.EqualTo(updateDesc))
			&& (goalInfo.followingSubGoalIndices == followingSubGoalIndices)
			&& (goalInfo.useRadius == useRadius)
			&& (goalInfo.radius == radius)
			&& (goalInfo.circleColor == circleColor)
			&& (goalInfo.goalClass == goalClass)
			&& (goalInfo.goalID == goalID)
			&& (goalInfo.failMeansQuest == failMeansQuest);
	}
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

USTRUCT()
struct FCompletedGoal
{
	GENERATED_BODY()
public:
	int goalIndex;
	FGoalInfo goalInfo;
	bool bSuccessful;
};

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UQuestStruct : public UObject
{
	GENERATED_BODY()
};
