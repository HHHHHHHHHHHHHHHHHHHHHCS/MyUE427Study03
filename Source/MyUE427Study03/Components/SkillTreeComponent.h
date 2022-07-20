// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyUE427Study03/Skill/SkillTreeStruct.h"
#include "MyUE427Study03/UserWidget/SkillTree/UI_SkillTree_Entry.h"
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

protected:
	class UUI_SkillTree_MainTree* mainTreeRef;
	
	// 技能树里面的内容是否已经设置好了
	bool bTreeSetup;

	// 技能树是否已经显示
	bool bTreeShow;
	
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

	void UpgradeSpell(ASkillBase* skill, UUI_SkillTree_Entry* entryWidget);

	void DowngradeSpell(ASkillBase* skill, UUI_SkillTree_Entry* entryWidget);

	void HandleShowCommand();
	
};
