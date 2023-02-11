// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestBase.h"

#include "QuestManager.h"
#include "MyUE427Study03/UserWidget/UserWidget_Main.h"
#include "MyUE427Study03/UserWidget/Quest/UI_QuestList_Entry.h"
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
	CalcGoalAmount();
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

bool AQuestBase::OnSubGoalCompleted(int subGoalIndex, bool isSuccess)
{
	if (currentGoalIndices.Contains(subGoalIndex))
	{
		currentGoalCount++;

		FGoalInfo completedGoal = questInfo.subGoals[subGoalIndex];

		if (completedGoal.bUpdateQuestDesc && isSuccess)
		{
			currentDescription = FText::FromString(currentDescription.ToString() + completedGoal.updateDesc.ToString());
			if (IsSelectedInJournal())
			{
				questManager->mainUI->questJournal->UpdateDesc();
			}
		}

		currentGoals.Remove(completedGoal);

		int widgetIndex = currentGoalIndices.Find(subGoalIndex);
		questUI->subGoalWidgets[widgetIndex]->RemoveFromParent();
		currentHuntedAmounts.RemoveAt(widgetIndex);
		questUI->subGoalWidgets.RemoveAt(widgetIndex);
		currentGoalIndices.Remove(subGoalIndex);

		if (isSuccess)
		{
			//子任务成功了

			completedSubGoals.Add(FCompletedGoal{subGoalIndex, completedGoal, true});

			if (completedGoal.failMeansQuest)
			{
				currentMustSucceedCount++;
			}

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
		}
		else
		{
			completedSubGoals.Add(FCompletedGoal{subGoalIndex, completedGoal, false});
			
			if (completedGoal.failMeansQuest)
			{
				//子任务失败 意味着整条任务线失败
				currentState = EQuestStates::FailedQuest;

				questManager->currentQuestFinished = true;

				for (int i : currentGoalIndices)
				{
					completedSubGoals.Add(FCompletedGoal{i, GoalAtIndex(i), false});
				}

				currentGoalIndices.Empty();
				currentHuntedAmounts.Empty();
				currentGoals.Empty();
				listEntryUI->RemoveFromParent();
				questUI->RemoveFromParent();
				questManager->OnQuestEnd(this);
				return true;
			}
			else
			{
				//任务失败 不影响整体任务线
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

				if (completedGoal.bUpdateQuestDesc)
				{
					currentDescription = FText::FromString(currentDescription.ToString() + completedGoal.updateDesc.ToString());
					if (IsSelectedInJournal())
					{
						questManager->mainUI->questJournal->UpdateDesc();
					}
				}
			}
		}

		// 总任务是否完成
		if (currentGoalCount >= totalGoalAmount)
		{
			questManager->currentQuestFinished = true;
			//所有的子任务都已经完成了
			if (currentMustSucceedCount >= totalMustSucceedAmount)
			{
				//所有必须要完成的任务都完成了
				currentState = EQuestStates::CompletedQuest;
			}
			else
			{
				currentState = EQuestStates::FailedQuest;
			}
			currentGoalIndices.Empty();
			currentHuntedAmounts.Empty();
			currentGoals.Empty();
			listEntryUI->RemoveFromParent();
			questUI->RemoveFromParent();
			questManager->OnQuestEnd(this);
			return true;
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

FGoalInfo AQuestBase::GoalAtIndex(int index)
{
	return questInfo.subGoals[index];
}

void AQuestBase::CalcGoalAmount()
{
	for (FGoalInfo info : questInfo.subGoals)
	{
		totalGoalAmount++;
		if (info.failMeansQuest)
		{
			totalMustSucceedAmount++;
		}
	}
}

// Called every frame
void AQuestBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
