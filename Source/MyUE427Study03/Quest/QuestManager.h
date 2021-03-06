// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestManager.generated.h"

UCLASS()
class MYUE427STUDY03_API AQuestManager : public AActor
{
	GENERATED_BODY()

public:
	class ACharacterBase* playerCharacter;
	class UUserWidget_Main* mainUI;

private:
	static AQuestManager* instance;

public:
	// Sets default values for this actor's properties
	AQuestManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FORCEINLINE static AQuestManager* GetInstance()
	{
		return instance;
	}
	
	void OnInit(ACharacterBase* _player, UUserWidget_Main* _mainUI);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
