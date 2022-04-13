// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyUE427Study03/Others/CursorDecal.h"
#include "MyUE427Study03/Skill/SkillBase.h"
#include "MyUE427Study03/Skill/SkillElementBase.h"
#include "MyUE427Study03/Skill/SkillEnum.h"
#include "MyUE427Study03/UserWidget/UserWidget_Main.h"
#include "CharacterBase.generated.h"

//技能的阶段(等级), 每一个等级的属性值不同
USTRUCT()
struct FSkillStage
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category="SkillData")
	int requiredLevel; //需要的前置等级
	
	UPROPERTY(EditAnywhere, Category="SkillData")
	TArray<ASkillBase*> requiredSkill; //需要的前置技能
	
	UPROPERTY(EditAnywhere, Category="SkillData")
	UTexture2D* overrideIcon; //覆盖用的新图标, 如果为空则使用初始技能和的图标

	UPROPERTY(EditAnywhere, Category="SkillData")
	float range; //技能效果的范围
	
	UPROPERTY(EditAnywhere, Category="SkillData")
	float damage; //技能的伤害值
	
	UPROPERTY(EditAnywhere, Category="SkillData")
	EDamageType damageType; //伤害的类型
	
	UPROPERTY(EditAnywhere, Category="SkillData")
	float criticalChance; //暴击率
	
	UPROPERTY(EditAnywhere, Category="SkillData")
	float cooldownTime; //技能的冷却时间
	
	UPROPERTY(EditAnywhere, Category="SkillData")
	float castingTime; //技能的释放的时间

	UPROPERTY(EditAnywhere, Category="SkillData")
	float manaCost; //魔法消耗值
	
	UPROPERTY(EditAnywhere, Category="SkillData")
	float missileSpeed; //投掷类速度
};

//技能的信息
USTRUCT()
struct FSkillInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category="SkillData")
	FText name;

	UPROPERTY(EditAnywhere, Category="SkillData")
	UTexture2D* icon;
	
	UPROPERTY(EditAnywhere, Category="SkillData")
	FText description; //技能的描述

	UPROPERTY(EditAnywhere, Category="SkillData")
	TSubclassOf<ASkillElementBase> skillElement; //技能所属的信息

	UPROPERTY(EditAnywhere, Category="SkillData")
	ETargetTypes target; //做用对象

	UPROPERTY(EditAnywhere, Category="SkillData")
	TArray<FSkillStage> stages; //技能所拥有的所有阶段, 通过SkillInfo来获取
};

UCLASS()
class MYUE427STUDY03_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	USpringArmComponent* cameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	UCameraComponent* followCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	USceneCaptureComponent2D* portraitComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	float minCameraZoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	float maxCameraZoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	float camerZoomStep;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player")
	APlayerController* playerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Move")
	TSubclassOf<ACursorDecal> cursorDecal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Move")
	float canMoveDistance;

protected:
	UPROPERTY(VisibleAnywhere, Category="PlayerInfo")
	FString currentName;

	UPROPERTY(VisibleAnywhere, Category="PlayerInfo")
	float totalHp;

	UPROPERTY(VisibleAnywhere, Category="PlayerInfo")
	float currentHp;

	UPROPERTY(VisibleAnywhere, Category="PlayerInfo")
	float totalMp;

	UPROPERTY(VisibleAnywhere, Category="PlayerInfo")
	float currentMp;

	UPROPERTY(VisibleAnywhere, Category="PlayerInfo")
	float currentExp;

	UPROPERTY(VisibleAnywhere, Category="PlayerInfo")
	int currentLevel;


protected:
	bool bMouseRightHold;

	bool bMouseMoving;

	ACursorDecal* currCursorDecal;

	UUserWidget_Main* mainUI;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MoveForward(float val);

	virtual void MoveRight(float val);

	virtual void MouseRightPressed();

	virtual void MouseRightReleased();

	virtual void AddControllerYawInput(float val) override;

	virtual void AddControllerPitchInput(float val) override;

	void OnSetDestinationPressed();

	void SetNewMoveDestination(const FVector& desLocation);

	void CameraZoomIn();

	void CameraZoomOut();

public:
	FORCEINLINE void SetCharacterName(FString name)
	{
		currentName = name;
	}

	FORCEINLINE FString GetCharacterName()
	{
		return currentName;
	}

	void ChangeCurrentHP(float deltaHP);

	FORCEINLINE float GetCurrentHP() const
	{
		return currentHp;
	}

	void ChangeCurrentMP(float deltaMp);

	FORCEINLINE float GetCurrentMP() const
	{
		return currentMp;
	}

	void ChangeCurrentExp(float deltaExp);

	FORCEINLINE float GetCurrentExp() const
	{
		return currentExp;
	}

	void SetLevel(int val);

	FORCEINLINE int GetLevel() const
	{
		return currentLevel;
	}

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CancelMoveToCursor();

	void ReadData();

	void UpdatePlayerDataUI();
};
