// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyUE427Study03/Skill/SkillTreeStruct.h"
#include "SkillTreeComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYUE427STUDY03_API USkillTreeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	class ACharacterBase* playerCharacter;

	// 技能点
	UPROPERTY(EditAnywhere, Category="Skill")
	int skillPoints = 2;

	UPROPERTY(EditAnywhere, Category="Skill")
	TArray<FSkillTreeCategory> categories;


public:
	// Sets default values for this component's properties
	USkillTreeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	bool BPlayerLearnedSpell(TSubclassOf<ASkillBase> skill);

	void AddSkillPoints(int amount);

	bool BCanUpgradeSpell(ASkillBase* skill);

	bool BSkillOnHotkey(ASkillBase* skill);
};
