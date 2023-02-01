// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestPropBase.h"

#include "MyUE427Study03/UserWidget/Quest/UI_Interaction.h"

// Sets default values
AQuestPropBase::AQuestPropBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	SetRootComponent(staticMesh);
	interactionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	interactionWidget->SetupAttachment(RootComponent);
	interactionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	interactionWidget->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	interactionWidget->SetCollisionProfileName(TEXT("NoCollision"));
	interactionWidget->SetGenerateOverlapEvents(false);
	interactionWidget->SetVisibility(false);

	static ConstructorHelpers::FClassFinder<UUserWidget> US(TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Quest/UI_Interaction.UI_Interaction_C'"));
	interactionWidget->SetWidgetClass(US.Class);
}

// Called when the game starts or when spawned
void AQuestPropBase::BeginPlay()
{
	Super::BeginPlay();

	UUI_Interaction* ui = Cast<UUI_Interaction>(interactionWidget->GetUserWidgetObject());
	ui->SetNameText(name);
	ui->SetInteractionText(FText::FromString("Press [F] to pick up"));
}

// Called every frame
void AQuestPropBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
