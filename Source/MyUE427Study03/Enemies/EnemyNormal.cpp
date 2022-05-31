// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemyNormal.h"
#include "EnemyNormal_Controller.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyUE427Study03/MyUE427Study03.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/Others/StaticLibrary.h"
#include "MyUE427Study03/UserWidget/UI_EnemyInfoWidget.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#define LOCTEXT_NAMESPACE "EnemyNameSpace"

// Sets default values
AEnemyNormal::AEnemyNormal()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	AIControllerClass = AEnemyNormal_Controller::StaticClass();
	aiPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISightConfig"));

	sightConfig->SightRadius = 800;
	sightConfig->LoseSightRadius = 2000;
	sightConfig->PeripheralVisionAngleDegrees = 90.0f;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;

	aiPerceptionComp->ConfigureSense(*sightConfig);
	//设置为视觉优先
	aiPerceptionComp->SetDominantSense(UAISense_Sight::StaticClass());

	enemyWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyWidget"));
	enemyWidgetComponent->SetupAttachment(GetRootComponent());
	static auto clsFinder = ConstructorHelpers::FClassFinder<UUI_EnemyInfoWidget>(TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Enemy/UI_EnemyInfo.UI_EnemyInfo_C'"));
	if (clsFinder.Succeeded())
	{
		enemyWidgetComponent->SetWidgetClass(clsFinder.Class);
		enemyWidgetComponent->SetDrawSize(FVector2D(200.0f, 60.0f));
		enemyWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		enemyWidgetComponent->SetTwoSided(true);
		enemyWidgetComponent->SetVisibility(false);
		enemyWidgetComponent->SetRelativeLocation(FVector(0, 0, 150));
		enemyWidgetComponent->SetRelativeRotation(FRotator(0, 0, 0));
		enemyWidgetComponent->SetVisibility(bInShowUIRange);
	}

	showUICollision = CreateDefaultSubobject<USphereComponent>(TEXT("ShowUICollision"));
	showUICollision->SetupAttachment(GetRootComponent());

	currentHealth = totalHealth;
}

// Called when the game starts or when spawned
void AEnemyNormal::BeginPlay()
{
	Super::BeginPlay();
	startLocation = GetActorLocation();
	myController = Cast<AEnemyNormal_Controller>(GetController());
	if (myController)
	{
		myController->Patrol();
	}
	enemyInfoWidget = Cast<UUI_EnemyInfoWidget>(enemyWidgetComponent->GetUserWidgetObject());
	aiPerceptionComp->OnPerceptionUpdated.AddDynamic(this, &AEnemyNormal::OnPerceptionUpdated);
	showUICollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyNormal::OnBeginOverlap_ShowUI);
	showUICollision->OnComponentEndOverlap.AddDynamic(this, &AEnemyNormal::OnEndOverlap_ShowUI);
	InitWidget();
	UpdateHealthBar();
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

void AEnemyNormal::Notify_AttackHit()
{
	AttackRay();
}

void AEnemyNormal::AttackRay()
{
	const float range = 180.0f;
	FVector startPos = GetActorLocation();
	FVector endPos = startPos + range * GetCapsuleComponent()->GetForwardVector();

	FHitResult hitResult;
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(this);
	const bool isHit = GetWorld()->LineTraceSingleByChannel(hitResult, startPos, endPos, EnemyHitChannel);
	if (isHit)
	{
		ACharacterBase* player = Cast<ACharacterBase>(hitResult.Actor);
		if (player)
		{
			player->OnReceiveDamage(baseDamage, critChance, attackDamageType, element, this, nullptr);
		}
	}
}

void AEnemyNormal::InitWidget()
{
	enemyInfoWidget->LevelName->SetText(FText::Format(LOCTEXT("EnemyNameSpace", "[Lv{0}.{1}]"), FText::AsNumber(level), enemyName));
	FLinearColor levelNameColor;
	if (bAggressive)
	{
		levelNameColor = FLinearColor::Red;
	}
	else
	{
		levelNameColor = FLinearColor::White;
	}
	enemyInfoWidget->LevelName->SetColorAndOpacity(levelNameColor);
}

void AEnemyNormal::OnBeginOverlap_ShowUI(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                         const FHitResult& SweepResult)
{
	if (bIsDead || bInShowUIRange)
	{
		return;
	}
	if (Cast<ACharacterBase>(OtherActor))
	{
		bInShowUIRange = true;
		enemyWidgetComponent->SetVisibility(true);
	}
}

void AEnemyNormal::OnEndOverlap_ShowUI(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bIsDead || !bInShowUIRange)
	{
		return;
	}
	if (Cast<ACharacterBase>(OtherActor))
	{
		bInShowUIRange = false;
		enemyWidgetComponent->SetVisibility(false);
	}
}

void AEnemyNormal::UpdateHealthBar()
{
	enemyInfoWidget->HealthBar->SetPercent(currentHealth / totalHealth);
}

void AEnemyNormal::ResetHealth()
{
	currentHealth = totalHealth;
	UpdateHealthBar();
}

void AEnemyNormal::ChangeHealth(float damage)
{
	currentHealth = FMath::Clamp(currentHealth + damage, 0.0f, totalHealth);
	UpdateHealthBar();
}


void AEnemyNormal::OnReceiveDamage(float attackerDamage, int attackerCritChance, EAttackDamageType type, TSubclassOf<AElementBase> attackElement, AActor* attacker,
                                   ASkillBase* skill)
{
	if (bIsDead || UStaticLibrary::IsEnemy(attacker))
	{
		return;
	}

	float damage = -UStaticLibrary::CalculateFinalDamage(attackerDamage, attackerCritChance, attackElement, element);
	ChangeHealth(damage);
	if (currentHealth <= 0)
	{
		OnDeath(attacker);
	}
	else
	{
		myController->OnAggroedPulled(attacker);
	}
}

void AEnemyNormal::OnDeath(AActor* killer)
{
	bIsDead = true;
	myController->animInst->Montage_Stop(0.0f);
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->StopMovementImmediately();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorHiddenInGame(true);
	ACharacterBase* player;
	if (UStaticLibrary::TryGetPlayer(killer, player))
	{
		player->ChangeCurrentExp(expForKill);
	}

	if(bDoesRespawn)
	{
		GetWorldTimerManager().SetTimer(timerHandle_Respawn, this, &AEnemyNormal::OnRespawn, respawnTime, false);
	}
	else
	{
		Destroy();
	}
}

void AEnemyNormal::OnRespawn()
{
	bIsDead = false;
	SetActorLocation(startLocation);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ChangeHealth(totalHealth);
	InitWidget();
	GetCharacterMovement()->MaxWalkSpeed = myController->patrolWalkSpeed;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	enemyWidgetComponent->SetVisibility(bInShowUIRange);
	SetActorHiddenInGame(true);
	myController->OnRespawn();
	myController->Patrol();
}


#undef LOCTEXT_NAMESPACE
