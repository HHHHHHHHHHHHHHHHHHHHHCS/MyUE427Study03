// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestEnum.generated.h"

//任务类型, 主线 支线
UENUM()
enum class EQuestCategories
{
	// 主线任务
	MainQuest,

	// 支线任务
	SideQuest,

	// 事件
	Events,
};

//任务目标的类型
UENUM()
enum class EGoalTypes
{
	//该NPC没有任务
	Custom,

	//刷怪
	Hunt,

	//搜索
	Find,

	//对话
	Talk,
};

//任务的区域
UENUM()
enum class ERegions
{
	BeiJing,

	NanJing,
};


/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UQuestEnum : public UObject
{
	GENERATED_BODY()
};

UENUM()
enum class EQuestStates
{
	CurrentQuest,
	CompletedQuest,
	FailedQuest,
};
