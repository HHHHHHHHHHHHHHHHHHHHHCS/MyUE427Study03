// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestStruct.h"
#include "GameFramework/Actor.h"
#include "QuestManager.generated.h"

UCLASS()
class MYUE427STUDY03_API AQuestManager : public AActor
{
	GENERATED_BODY()

public:
	class ACharacterBase* playerCharacter;
	class UUserWidget_Main* mainUI;

	class AQuestBase* currentQuest; //当前处理的任务

	TArray<TSubclassOf<AQuestBase>> allQuestClasses;
	TArray<AQuestBase*> questActors;
	FGoalInfo currentSubGoal;

private:
	static AQuestManager* instance;

public:
	// Sets default values for this actor's properties
	AQuestManager();


	void SelectNewQuest(AQuestBase* newQuest, class UUI_Quest_SubGoal* uiSubGoal);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool AddNewQuest(TSubclassOf<AQuestBase> questCls);

public:
	FORCEINLINE static AQuestManager* GetInstance()
	{
		return instance;
	}

	void OnInit(ACharacterBase* _player, UUserWidget_Main* _mainUI);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
