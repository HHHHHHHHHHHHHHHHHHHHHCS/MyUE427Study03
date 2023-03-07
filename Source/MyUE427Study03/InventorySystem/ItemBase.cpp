// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

#include "Inventory.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/UserWidget/Quest/UI_Interaction.h"

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
	interactionUI->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
	interactionUI->SetCollisionProfileName(TEXT("NoCollision"));
	interactionUI->SetGenerateOverlapEvents(false);
	interactionUI->SetVisibility(false);

	static ConstructorHelpers::FClassFinder<UUserWidget> uiCls(TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Quest/UI_Interaction.UI_Interaction_C'"));
	interactionUI->SetWidgetClass(uiCls.Class);

	amount = 1;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	auto widget = Cast<UUI_Interaction>(interactionUI->GetUserWidgetObject());
	widget->SetNameText(itemInfo.name);
	widget->SetInteractionText(FText::FromString("Press [F] to pick up!"));
	remainder = amount;
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::OnEnterPlayerRadius(ACharacterBase* character)
{
	interactionUI->SetVisibility(true);
}

void AItemBase::OnLeavePlayerRadius(ACharacterBase* character)
{
	interactionUI->SetVisibility(false);
}

void AItemBase::OnInteractWith(ACharacterBase* character)
{
	remainder = character->inventoryRef->AddItem(GetClass(), remainder);
	if (remainder <= 0)
	{
		Destroy();
	}
}

void AItemBase::OnUsed()
{
	if(inventoryRef->RemoveItemAtIndex(index, 1))
	{
		Destroy();
	}
}
