// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeComponent.h"

#include "MyUE427Study03/Characters/CharacterBase.h"

// Sets default values for this component's properties
USkillTreeComponent::USkillTreeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkillTreeComponent::BeginPlay()
{
	Super::BeginPlay();

	playerCharacter = Cast<ACharacterBase>(GetOwner());
}


// Called every frame
void USkillTreeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USkillTreeComponent::BPlayerLearnedSpell(TSubclassOf<ASkillBase> skill)
{
	return playerCharacter->learnedSkills.Contains(skill);
}

void USkillTreeComponent::AddSkillPoints(int amount)
{
	skillPoints += amount;
}

bool USkillTreeComponent::BCanUpgradeSpell(ASkillBase* skill)
{
	// 1.技能点>0 2.主角当前的等级>下阶段需求等级 3.技能等级不能溢出
	if (skillPoints > 0 && playerCharacter->GetCurrentLevel() >= skill->GetNextStage().requiredLevel
		&& skill->GetCurrentStageIndex() < skill->skillInfo.stages.Num() - 1)
	{
		bool result = true;
		//如果有一个前置技能没有学习 则返回false
		for(const auto& preSkill : skill->GetNextStage().requiredSkills)
		{
			if(!BPlayerLearnedSpell(preSkill))
			{
				result = false;
				break;
			}
		}
		return result;
	}
	return false;
}

bool USkillTreeComponent::BSkillOnHotkey(ASkillBase* skill)
{
	bool result = false;
	for(const auto& item : playerCharacter->mainUI->GetAllHotKeySlots())
	{
		if(item->assignedSpell && item->assignedSpell == skill)
		{
			result = true;
			break;
		}
	}
	return result;
}
