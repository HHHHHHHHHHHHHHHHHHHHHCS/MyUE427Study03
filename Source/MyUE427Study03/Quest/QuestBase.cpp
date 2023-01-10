// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestBase.h"

#include "QuestManager.h"
#include "MyUE427Study03/UserWidget/UserWidget_Main.h"
#include "MyUE427Study03/UserWidget/Quest/UI_Quest_Journal.h"
#include "MyUE427Study03/UserWidget/Quest/UI_Quest_Quest.h"
#include "MyUE427Study03/UserWidget/Quest/UI_Quest_SubGoal.h"

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
	currentDescription = questInfo.desc;
	currentHuntedAmounts.SetNum(currentGoalIndices.Num());
}

bool AQuestBase::OnSubGoalCompleted(int subGoalIndex)
{
	if (currentGoalIndices.Contains(subGoalIndex))
	{
		FGoalInfo completedGoal = questInfo.subGoals[subGoalIndex];
		completedSubGoals.Add(FCompletedGoal{subGoalIndex, completedGoal, true});
		currentGoals.Remove(completedGoal);

		if (completedGoal.bUpdateQuestDesc)
		{
			currentDescription = FText::FromString(currentDescription.ToString() + completedGoal.updateDesc.ToString());
			if (IsSelectedInJournal())
			{
				questManager->mainUI->questJournal->UpdateDesc();
			}
		}

		int widgetIndex = currentGoalIndices.Find(subGoalIndex);
		questUI->subGoalWidgets[widgetIndex]->RemoveFromParent();
		currentHuntedAmounts.RemoveAt(widgetIndex);
		questUI->subGoalWidgets.RemoveAt(widgetIndex);
		currentGoalIndices.Remove(subGoalIndex);

		for (int i : completedGoal.followingSubGoalIndices)
		{
			currentGoalIndices.Add(i);
			currentGoals.Add(questInfo.subGoals[i]);

			if (i > currentHuntedAmounts.Num())
			{
				currentHuntedAmounts.Add(0);
			}

			auto cls = LoadClass<UUI_Quest_SubGoal>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Quest/UI_SubGoal.UI_SubGoal_C'"));
			UUI_Quest_SubGoal* subGoalUI = CreateWidget<UUI_Quest_SubGoal>(GetWorld(), cls);
			subGoalUI->goalInfo = questInfo.subGoals[i];
			subGoalUI->assignedQuest = this;
			subGoalUI->questWidget = questUI;


			questUI->subGoalWidgets.Add(subGoalUI);
			questUI->VBOX_SubGoal->AddChild(subGoalUI);
		}

		if (IsSelectedInJournal())
		{
			questManager->mainUI->questJournal->GenerateSubGoals();
		}

		if (subGoalIndex == selectedSubGoalIndex && questUI->subGoalWidgets.Num() > 0)
		{
			questUI->SelectSubGoal(questUI->subGoalWidgets[0]);
		}

		return true;
	}
	else
	{
		return false;
	}
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

bool AQuestBase::IsSelectedInJournal()
{
	auto selectQuest = questManager->mainUI->questJournal->selectedQuest;
	return selectQuest && selectQuest == this;
}

// Called every frame
void AQuestBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
