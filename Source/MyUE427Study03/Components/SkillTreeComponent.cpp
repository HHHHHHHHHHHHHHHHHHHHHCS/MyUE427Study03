// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeComponent.h"

#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/UserWidget/SkillTree/UI_SkillTree_Connection.h"
#include "MyUE427Study03/UserWidget/SkillTree/UI_SkillTree_MainTree.h"

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
		for (const auto& preSkill : skill->GetNextStage().requiredSkills)
		{
			if (!BPlayerLearnedSpell(preSkill))
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
	for (const auto& item : playerCharacter->mainUI->GetAllHotKeySlots())
	{
		if (item->assignedSpell && item->assignedSpell == skill)
		{
			result = true;
			break;
		}
	}
	return result;
}

void USkillTreeComponent::UpgradeSpell(ASkillBase* skill, UUI_SkillTree_Entry* entryWidget)
{
	this->upgradeSkill = skill;
	this->entryUI = entryWidget;

	if (BCanUpgradeSpell(skill))
	{
		skillPoints -= 1;
		skill->InCreaseCurrentStageIndex();
		if (skill->GetCurrentStageIndex() == 0)
		{
			// 第一次学习这个技能
			playerCharacter->learnedSkills.Add(skill->GetClass());
			entryWidget->OnSpellLearned();
			ActiveConnections(skill->GetClass());

			entryWidget->UpdateStageText();
			entryWidget->UpdateIcon();
			mainTreeRef->UpdateSP();
			UpdateAllEntries();
		}
		else
		{
			entryWidget->UpdateStageText();
			entryWidget->UpdateIcon();
			mainTreeRef->UpdateSP();
			UpdateAllEntries();
		}
	}
}

void USkillTreeComponent::DowngradeSpell(ASkillBase* skill, UUI_SkillTree_Entry* entryWidget)
{
	this->upgradeSkill = skill;
	this->entryUI = entryWidget;

	skill->DeCreaseCurrentStageIndex();
	skillPoints += 1;
	entryWidget->UpdateStageText();
	entryWidget->UpdateIcon();
	mainTreeRef->UpdateSP();
	UpdateAllEntries();
}

void USkillTreeComponent::HandleShowCommand()
{
	if (bTreeSetup)
	{
		if (playerCharacter->mainUI->bSkillTreeShow)
		{
			mainTreeRef->SetVisibility(ESlateVisibility::Hidden);
			playerCharacter->mainUI->bSkillTreeShow = false;
		}
		else
		{
			mainTreeRef->SetVisibility(ESlateVisibility::Visible);
			FInputModeGameAndUI inputMode;
			playerCharacter->playerController->SetInputMode(inputMode);
			playerCharacter->mainUI->bSkillTreeShow = true;
		}
	}
}

void USkillTreeComponent::SetupTree()
{
	mainTreeRef = playerCharacter->mainUI->skillTree_MainTree;
	if (mainTreeRef)
	{
		mainTreeRef->MyInitialize(this);
		bTreeSetup = true;
	}
}

void USkillTreeComponent::ActiveConnections(TSubclassOf<ASkillBase> forSkill)
{
	for (auto& subTree : mainTreeRef->subTreeWidgets)
	{
		for (auto& connection : subTree->connections)
		{
			if (connection->forSKill == forSkill)
			{
				connection->Active();
			}
		}
	}
}

void USkillTreeComponent::UpdateAllEntries()
{
	for (auto& subTree : mainTreeRef->subTreeWidgets)
	{
		for (auto& entry : subTree->skillEntries)
		{
			entry->UpdateUpgradeBox();
		}
	}
}
