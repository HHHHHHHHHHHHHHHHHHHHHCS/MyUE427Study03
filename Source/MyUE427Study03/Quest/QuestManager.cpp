// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

AQuestManager* AQuestManager::instance = nullptr;

// Sets default values
AQuestManager::AQuestManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuestManager::BeginPlay()
{
	Super::BeginPlay();
}

void AQuestManager::OnInit(ACharacterBase* _player, UUserWidget_Main* _mainUI)
{
	instance = this;
	playerCharacter = _player;
	mainUI = _mainUI;
}

// Called every frame
void AQuestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



