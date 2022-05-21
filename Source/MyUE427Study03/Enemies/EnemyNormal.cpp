// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyNormal.h"

#include "EnemyNormal_Controller.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AEnemyNormal::AEnemyNormal()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	startLocation = GetActorLocation();

	AIControllerClass = AEnemyNormal_Controller::StaticClass();
	aiPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));

	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISightConfig"));
	sightConfig->SightRadius = 800;
	sightConfig->LoseSightRadius = 2000;
	sightConfig->PeripheralVisionAngleDegrees = 90.0f;

	aiPerceptionComp->ConfigureSense(*sightConfig);
	//设置为视觉优先
	aiPerceptionComp->SetDominantSense(UAISense_Sight::StaticClass());
	aiPerceptionComp->OnPerceptionUpdated.AddDynamic(this, &AEnemyNormal::OnPerceptionUpdated);
}

// Called when the game starts or when spawned
void AEnemyNormal::BeginPlay()
{
	Super::BeginPlay();
	myController = Cast<AEnemyNormal_Controller>(GetController());
	if(myController)
	{
		myController->Patrol();
	}
}

// Called every frame
void AEnemyNormal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyNormal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyNormal::OnPerceptionUpdated(const TArray<AActor*>& updatedActors)
{
	if (!bAggressive || myController->bWasAggroed)
	{
		return;
	}

	for (auto& actor : updatedActors)
	{
		ACharacterBase* charcter = Cast<ACharacterBase>(actor);
		if (charcter)
		{
			myController->OnAggroedPulled(charcter);
		}
	}
}
