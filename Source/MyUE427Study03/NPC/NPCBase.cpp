// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCBase.h"

#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/UserWidget/Quest/UI_Interaction.h"

// Sets default values
ANPCBase::ANPCBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	interactionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	interactionWidget->SetupAttachment(RootComponent);
	interactionWidget->SetVisibility(false);
}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	Cast<UUI_Interaction>(interactionWidget->GetUserWidgetObject())->SetNameText(name);
}

// Called every frame
void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANPCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANPCBase::OnEnterPlayerRadius(ACharacterBase* character)
{
	interactionWidget->SetVisibility(true);
}

void ANPCBase::OnLeavePlayerRadius(ACharacterBase* character)
{
	interactionWidget->SetVisibility(false);
}

void ANPCBase::OnInteractWith(ACharacterBase* character)
{
	if(!character->questManager->allQuestClasses.Contains(myQuest))
	{
		character->questManager->AddNewQuest(myQuest);
	}
}
