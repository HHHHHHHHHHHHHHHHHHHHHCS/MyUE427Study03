// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SkillDragOperation.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API USkillDragOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	class UUI_SkillHotkey* FromHotkey;//当前保存的是哪一个快捷键， 从哪一个快捷键拖拽过来的
	class ASkillBase* skillActor;//当前拖拽的是哪一个技能

public:
};
