// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalActor.h"
#include "GameFramework/Character.h"
#include "Paper2D/Classes/PaperSprite.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoalActor::AGoalActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	defaultRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComp"));
	RootComponent = defaultRootComp;
	minimapIcon = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MinimapIcon"));
	minimapIcon->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> minimapSprite(TEXT("PaperSprite'/Game/Textures/UI/QuestTextures/NpcIcon_Sprite.NpcIcon_Sprite'"));
	if (minimapSprite.Succeeded())
	{
		minimapIcon->SetSprite(minimapSprite.Object);
	}

	minimapIcon->SetRelativeLocation(FVector(0, 0, 150));
	minimapIcon->SetRelativeRotation(FRotator(0, 0, 90));
	minimapIcon->SetRelativeScale3D(FVector(2, 2, 2));
	minimapIcon->SetGenerateOverlapEvents(false);
	// minimapIcon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// minimapIcon->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	minimapIcon->SetCollisionProfileName(TEXT("NoCollision"));
	
	questAreaIcon = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("QuestAreaIcon"));
	questAreaIcon->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> questAreaSprite(TEXT("PaperSprite'/Game/Textures/UI/QuestTextures/GoalCircle_Sprite.GoalCircle_Sprite'"));
	if (questAreaSprite.Succeeded())
	{
		questAreaIcon->SetSprite(questAreaSprite.Object);
	}
	questAreaIcon->SetRelativeLocation(FVector(0, 0, 150));
	questAreaIcon->SetRelativeRotation(FRotator(0, 0, 90));
	// questAreaIcon->SetRelativeScale3D(FVector(2, 2, 2));
	questAreaIcon->SetGenerateOverlapEvents(false);
	// questAreaIcon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// questAreaIcon->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	questAreaIcon->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AGoalActor::BeginPlay()
{
	Super::BeginPlay();
	SetOwner(UGameplayStatics::GetPlayerCharacter(this, 0));
	minimapIcon->SetOwnerNoSee(true);
	questAreaIcon->SetOwnerNoSee(true);
}

// Called every frame
void AGoalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
