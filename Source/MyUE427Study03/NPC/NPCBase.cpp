// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCBase.h"

#include "Kismet/GameplayStatics.h"
#include "PaperSprite.h"
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
	interactionWidget->SetCollisionProfileName(TEXT("NoCollision"));
	interactionWidget->SetGenerateOverlapEvents(false);
	interactionWidget->SetWidgetSpace(EWidgetSpace::Screen);

	questIcon = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("QuestIcon"));
	questIcon->SetupAttachment(RootComponent);
	questIcon->SetRelativeLocation(FVector(0, 0, 150));
	questIcon->SetRelativeRotation(FRotator(180, 90, 180));
	questIcon->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
	questIcon->SetSpriteColor(FLinearColor::Yellow);
	questIcon->SetCollisionProfileName(TEXT("NoCollision"));
	questIcon->SetGenerateOverlapEvents(false);

	static auto questIconSprite = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Textures/UI/QuestTextures/Quest_Icon_Sprite.Quest_Icon_Sprite'"));
	if (questIconSprite.Succeeded())
	{
		questIcon->SetSprite(questIconSprite.Object);
	}
}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	questIcon->SetWorldRotation(FRotator(0, 88.5f, -90));
	Cast<UUI_Interaction>(interactionWidget->GetUserWidgetObject())->SetNameText(name);
	questIcon->SetVisibility(bHasQuest);
	SetOwner(UGameplayStatics::GetPlayerCharacter(this, 0));
	questIcon->SetOwnerNoSee(true);
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
	if (!character->questManager->allQuestClasses.Contains(myQuest))
	{
		character->questManager->AddNewQuest(myQuest);
		questIcon->SetVisibility(false);
	}
}
