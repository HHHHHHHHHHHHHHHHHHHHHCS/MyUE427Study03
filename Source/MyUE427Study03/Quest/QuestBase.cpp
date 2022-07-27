// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestBase.h"

// Sets default values
AQuestBase::AQuestBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuestBase::BeginPlay()
{
	Super::BeginPlay();
}

void AQuestBase::UpdateSubGoals()
{
	currentGoals.Empty();
	for (int i = 0; i < currentGoalIndices.Num(); i++)
	{
		currentGoals.Add(questInfo.subGoals[currentGoalIndices[i]]);
	}
}

void AQuestBase::SetupStartingGoals()
{
	currentGoalIndices.Empty();
	currentGoalIndices = startingSubGoalIndices;
	UpdateSubGoals();
}

bool AQuestBase::GoToNextSubGoal()
{
	if ((currentGoalIndices.Max() + 1) <= questInfo.subGoals.Num())
	{
		int nextIndex = currentGoalIndices.Max() + 1;
		currentGoalIndices.Empty();
		currentGoalIndices.Add(nextIndex);
		UpdateSubGoals();
		return true;
	}
	else
	{
		return false;
	}
}

// Called every frame
void AQuestBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
