// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slate/WidgetTransform.h"
#include "UObject/NoExportTypes.h"
#include "SkillTreeStruct.generated.h"

USTRUCT()
struct FSkillTreeConnection
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Skill")
	FVector2D position;

	UPROPERTY(EditAnywhere, Category="Skill")
	FVector2D size;

	UPROPERTY(EditAnywhere, Category="Skill")
	FWidgetTransform transform;

	TSubclassOf<class ASkillBase> forSpell; //该技能所需要的前置技能
};

USTRUCT()
struct FSubTreeEntry
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Skill")
	FVector2D position;

	UPROPERTY(EditAnywhere, Category="Skill")
	TSubclassOf<class ASkillBase> spellClass;
};

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API USkillTreeStruct : public UObject
{
	GENERATED_BODY()
};
