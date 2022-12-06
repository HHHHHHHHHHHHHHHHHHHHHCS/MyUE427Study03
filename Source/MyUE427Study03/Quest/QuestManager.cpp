// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

#include "QuestBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/UserWidget/UserWidget_Main.h"
#include "MyUE427Study03/UserWidget/Quest/UI_Quest_Quest.h"

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

void AQuestManager::SelectNewQuest(AQuestBase* newQuest, UUI_Quest_SubGoal* uiSubGoal)
{
	if (currentQuest)
	{
		currentQuest->questUI->Text_QuestName->SetIsEnabled(false);
		currentQuest->questUI->SelectSubGoal(nullptr);
	}

	currentQuest = newQuest;
	currentQuest->questUI->OnQuestSelected(uiSubGoal);
}

bool AQuestManager::AddNewQuest(TSubclassOf<AQuestBase> questCls)
{
	if (questCls && !allQuestClasses.Contains(questCls))
	{
		allQuestClasses.Add(questCls);
		AQuestBase* tempQuest = GetWorld()->SpawnActor<AQuestBase>(questCls, FVector::ZeroVector, FRotator::ZeroRotator);
		questActors.Add(tempQuest);
		tempQuest->SetupStartingGoals();
		tempQuest->questUI = mainUI->AddQuestToList(tempQuest);
		tempQuest->questUI->questManager = this;
		tempQuest->questUI->UpdateQuest();
		// 如果是第一个就默认选择
		if (questActors.Num() <= 1)
		{
			SelectNewQuest(tempQuest, tempQuest->questUI->subGoalWidgets[0]);
		}
		else
		{
			tempQuest->questUI->Text_QuestName->SetIsEnabled(false);
		}
		playerCharacter->PlayAddNewAnim();
		return true;
	}
	else
	{
		return false;
	}
}

void AQuestManager::OnInit(ACharacterBase* _player, UUserWidget_Main* _mainUI)
{
	instance = this;
	playerCharacter = _player;
	mainUI = _mainUI;
	mainUI->minimapWidget->SetGoalHitVisible(false);
}

// Called every frame
void AQuestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AQuestManager::GetDistanceToGoal()
{
	return FMath::FloorToInt(FVector::Dist2D(playerCharacter->GetActorLocation(), currentGoal->GetActorLocation()) / 100.0f);
}

void AQuestManager::UpdateDirectionArrow()
{
	FRotator rotator = UKismetMathLibrary::FindLookAtRotation(playerCharacter->GetActorLocation(), currentGoal->GetActorLocation());
	mainUI->minimapWidget->RotateDirectionArrow(rotator.Yaw);
}

void AQuestManager::OnSwitchSubQuest()
{
	if (currentGoal)
	{
		currentGoal->Destroy();
	}
	currentSubGoal = currentQuest->questInfo.subGoals[currentQuest->selectedSubGoalIndex];

	if (currentSubGoal.goalLocation.bHasLocation)
	{
		currentGoal = GetWorld()->SpawnActor<AGoalActor>(goalActorCls, currentSubGoal.goalLocation.location, FRotator::ZeroRotator);
		currentGoal->InitializeMinimapIcon(currentSubGoal.useRadius, currentSubGoal.radius, currentSubGoal.circleColor);
		float dist = GetDistanceToGoal();
		mainUI->minimapWidget->SetDistanceText(dist);
		UpdateDirectionArrow();
		if (GetDistanceToGoal() > ShowHintDistance)
		{
			mainUI->minimapWidget->SetGoalHitVisible(true);
		}
		else
		{
			mainUI->minimapWidget->SetGoalHitVisible(false);
		}
	}
	else
	{
		currentGoal = nullptr;
		mainUI->minimapWidget->SetGoalHitVisible(false);
	}
}

void AQuestManager::OnPlayMove()
{
	if (currentGoal)
	{
		mainUI->minimapWidget->SetDistanceText(GetDistanceToGoal());
		UpdateDirectionArrow();
		if (GetDistanceToGoal() > ShowHintDistance)
		{
			mainUI->minimapWidget->SetGoalHitVisible(true);
		}
		else
		{
			mainUI->minimapWidget->SetGoalHitVisible(false);
		}
	}
}
