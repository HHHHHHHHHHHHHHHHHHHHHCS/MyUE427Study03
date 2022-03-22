// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyUE427Study03/MyUE427Study03.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	cameraBoom->SetupAttachment(GetRootComponent());
	cameraBoom->TargetArmLength = 600.0f;
	cameraBoom->SetRelativeRotation(FRotator(-30, 0, 0));

	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom);

	bUseControllerRotationYaw = false;
	cameraBoom->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	mouseRightHold = false;
	canMoveDistance = 120.0f;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	playerController = Cast<APlayerController>(GetController());
	playerController->bShowMouseCursor = true;
}

void ACharacterBase::MoveForward(float val)
{
	if (val == 0 || Controller == nullptr)
	{
		return;
	}

	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(direction, val);
}

void ACharacterBase::MoveRight(float val)
{
	if (val == 0 || Controller == nullptr)
	{
		return;
	}

	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(direction, val);
}

void ACharacterBase::MouseRightPressed()
{
	mouseRightHold = true;
}

void ACharacterBase::MouseRightReleased()
{
	mouseRightHold = false;
}

void ACharacterBase::AddControllerYawInput(float val)
{
	if (val == 0 || mouseRightHold == false)
	{
		return;
	}
	Super::AddControllerYawInput(val);
}

void ACharacterBase::AddControllerPitchInput(float val)
{
	if (val == 0 || mouseRightHold == false)
	{
		return;
	}
	Super::AddControllerPitchInput(val);
}

void ACharacterBase::OnSetDestinationPressed()
{
	FHitResult hitResult;
	playerController->GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
	if (hitResult.bBlockingHit)
	{
		if (hitResult.GetActor()->GetComponentsCollisionResponseToChannel(CursorTraceChannel)
			== ECollisionResponse::ECR_Block)
		{
			FActorSpawnParameters parameters;
			parameters.Owner = this;
			GetWorld()->SpawnActor<ACursorDecal>(cursorDecal, hitResult.Location, FRotator::ZeroRotator, parameters);
			SetNewMoveDestination(hitResult.Location);
		}
	}
}

void ACharacterBase::SetNewMoveDestination(const FVector& desLocation) const
{
	const float dist = FVector::Dist(desLocation, GetActorLocation());
	if (dist >= canMoveDistance)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(playerController, desLocation);
	}
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacterBase::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &ACharacterBase::AddControllerPitchInput);
	PlayerInputComponent->BindAction("MouseRight", EInputEvent::IE_Pressed, this, &ACharacterBase::MouseRightPressed);
	PlayerInputComponent->BindAction("MouseRight", EInputEvent::IE_Released, this, &ACharacterBase::MouseRightReleased);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacterBase::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACharacterBase::StopJumping);
	PlayerInputComponent->BindAction("MouseLeft", EInputEvent::IE_Pressed, this,
	                                 &ACharacterBase::OnSetDestinationPressed);
}
