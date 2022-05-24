// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyUE427Study03/Interface/DamageableInterface.h"
#include "MyUE427Study03/Others/CursorDecal.h"
#include "MyUE427Study03/Skill/SkillElementBase.h"
#include "MyUE427Study03/UserWidget/UserWidget_Main.h"
#include "CharacterBase.generated.h"

UCLASS()
class MYUE427STUDY03_API ACharacterBase : public ACharacter, public IDamageableInterface
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


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TArray<FKey> keys;

	UPROPERTY(EditAnywhere, Category="UI")
	int keysPerRow;

	UPROPERTY(EditAnywhere, Category="Skill")
	TSubclassOf<ASkillElementBase> skillElement;

	UPROPERTY(EditAnywhere, Category="Skill")
	TArray<TSubclassOf<ASkillBase>> startingSkills; //初始技能

	bool bCanFindKey;

	UUserWidget_Main* mainUI;

protected:
	bool bMouseRightHold;

	bool bMouseMoving;

	bool bIsCasting;

	ACursorDecal* currCursorDecal;

	UPROPERTY(BlueprintReadOnly)
	ASkillBase* currentSkill; //释放的当前技能


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

	void OnAnyKeyPressed(FKey key);


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

	//生成初始技能
	void GenerateStartingSkills();

	//开始技能释放
	void BeginSpellCast(ASkillBase* skill);

	//结束技能释放
	void EndSpellCast(ASkillBase* skill);

	FORCEINLINE bool GetBIsCasting() const
	{
		return bIsCasting;
	}

	virtual void OnReceiveDamage(float baseDamage, int critChance, ESkillDamageType type,
	                             TSubclassOf<ASkillElementBase> attackElement, AActor* attacker, ASkillBase* skill) override;
};
