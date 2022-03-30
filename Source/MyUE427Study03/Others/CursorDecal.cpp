// Fill out your copyright notice in the Description page of Project Settings.


#include "CursorDecal.h"

#include "Components/DecalComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACursorDecal::ACursorDecal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(sceneRoot);

	cursorToWorld = CreateDefaultSubobject<UDecalComponent>(TEXT("CursorDecal"));
	cursorToWorld->SetupAttachment(sceneRoot);
	cursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	cursorToWorld->SetRelativeRotation(FRotator(90, 0, 0));

	const auto materialFinder = ConstructorHelpers::FObjectFinder<UMaterial>(
		TEXT("Material'/Game/Materials/Others/Mat_Cursor_Decal.Mat_Cursor_Decal'"));

	if (materialFinder.Succeeded())
	{
		cursorToWorld->SetDecalMaterial(materialFinder.Object);
	}

	boxComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	boxComponent->SetBoxExtent(FVector(32.0f, 32.0f, 20.0f));
	boxComponent->SetupAttachment(sceneRoot);
}

// Called when the game starts or when spawned
void ACursorDecal::BeginPlay()
{
	Super::BeginPlay();

	//不能在构造函数中
	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACursorDecal::OnBeginOverlap);
}

// Called every frame
void ACursorDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 不用通知模式的 碰撞 触发
// void ACursorDecal::NotifyActorBeginOverlap(AActor* OtherActor)
// {
// 	Super::NotifyActorBeginOverlap(OtherActor);
//
// 	if (OtherActor == GetOwner())
// 	{
// 		Destroy();
// 	}
// }

void ACursorDecal::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	// GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, TEXT("!!!!!!"));

	if (OtherActor == GetOwner())
	{
		Destroy();
	}
}
