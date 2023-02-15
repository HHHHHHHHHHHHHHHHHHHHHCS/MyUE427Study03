// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

// Sets default values
AItemBase::AItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComp"));
	SetRootComponent(sphereCollisionComp);

	staticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	staticMeshComp->SetupAttachment(RootComponent);

	interactionUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionUI"));
	interactionUI->SetupAttachment(RootComponent);
	interactionUI->SetWidgetSpace(EWidgetSpace::Screen);
	interactionUI->SetRelativeScale3D(FVector(0.7f,0.7f,0.7f));
	interactionUI->SetCollisionProfileName(TEXT("NoCollision"));
	interactionUI->SetGenerateOverlapEvents(false);
	interactionUI->SetVisibility(false);

	static ConstructorHelpers::FClassFinder<UUserWidget> uiCls(TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Quest/UI_Interaction.UI_Interaction_C'"));
	interactionUI->SetWidgetClass(uiCls.Class);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
