// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "CharacterInfo.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/DataTable.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyUE427Study03/MyUE427Study03.h"
#include "MyUE427Study03/Others/StaticLibrary.h"
#include "MyUE427Study03/Skill/SkillBase.h"
#include "MyUE427Study03/Skill/SkillEnum.h"
#include "MyUE427Study03/UserWidget/UserWidget_Main.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	cameraBoom->SetupAttachment(GetRootComponent());
	cameraBoom->TargetArmLength = 600.0f;
	cameraBoom->SetRelativeRotation(FRotator(-30, 0, 0));
	minCameraZoom = 75.0f;
	maxCameraZoom = 1000.0f;
	camerZoomStep = 25.0f;

	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom);

	portraitComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("PortraitComponent"));
	portraitComponent->SetupAttachment(GetMesh(), "head");
	portraitComponent->SetRelativeLocation(FVector(0, 70, 0));
	portraitComponent->SetRelativeRotation(FRotator(0, -90, 90));
	portraitComponent->FOVAngle = 30.0f;
	static auto portraitRT = ConstructorHelpers::FObjectFinder<UTexture>(
		TEXT("TextureRenderTarget2D'/Game/Blueprints/Others/RT_Protrait.RT_Protrait'"));
	if (portraitRT.Succeeded())
	{
		portraitComponent->TextureTarget = Cast<UTextureRenderTarget2D>(portraitRT.Object);
	}

	bUseControllerRotationYaw = false;
	cameraBoom->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	//FClassFinder 的path 不需要前缀和后缀
	static ConstructorHelpers::FClassFinder<ACursorDecal> cursorDecalCls(
		TEXT("'/Game/Blueprints/Others/BP_CursorDecal'"));
	if (cursorDecalCls.Succeeded())
	{
		cursorDecal = cursorDecalCls.Class;
	}

	bMouseRightHold = false;
	canMoveDistance = 0.0f;
	bMouseMoving = false;
	bCanFindKey = true;

	ReadData();
	currentLevel = 1;

	//Keys
	{
		keysPerRow = 9;
		keys.Add(EKeys::One);
		keys.Add(EKeys::Two);
		keys.Add(EKeys::Three);
		keys.Add(EKeys::Four);
		keys.Add(EKeys::Five);
		keys.Add(EKeys::Six);
		keys.Add(EKeys::Seven);
		keys.Add(EKeys::Eight);
		keys.Add(EKeys::Nine);
		keys.Add(EKeys::F1);
		keys.Add(EKeys::F2);
		keys.Add(EKeys::F3);
		keys.Add(EKeys::F4);
		keys.Add(EKeys::F5);
		keys.Add(EKeys::F6);
		keys.Add(EKeys::F7);
		keys.Add(EKeys::F8);
		keys.Add(EKeys::F9);
	}
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	playerController = Cast<APlayerController>(GetController());
	playerController->bShowMouseCursor = true;

	//查找UserWidget这种 需要在路径地址末尾加_C
	mainUI = CreateWidget<UUserWidget_Main>(GetWorld(), LoadClass<UUserWidget_Main>(
		                                        this,TEXT(
			                                        "WidgetBlueprint'/Game/Blueprints/UserWidget/UI_Main.UI_Main_C'")));
	mainUI->AddToViewport();
	mainUI->GenerateHotkeys(keys, keysPerRow);
	UpdatePlayerDataUI();
	GenerateStartingSkills();
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
	PlayerInputComponent->BindAction("MouseLeft", EInputEvent::IE_Pressed, this, &ACharacterBase::OnSetDestinationPressed);
	PlayerInputComponent->BindAction("ZoomIn", EInputEvent::IE_Pressed, this, &ACharacterBase::CameraZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", EInputEvent::IE_Pressed, this, &ACharacterBase::CameraZoomOut);
	PlayerInputComponent->BindAction("AnyKey", EInputEvent::IE_Pressed, this, &ACharacterBase::OnAnyKeyPressed);
}

void ACharacterBase::MoveForward(float val)
{
	if (val == 0 || Controller == nullptr)
	{
		return;
	}

	//val==0 也在调用
	if (bMouseMoving)
	{
		CancelMoveToCursor();
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

	//val==0 也在调用
	if (bMouseMoving)
	{
		CancelMoveToCursor();
	}

	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(direction, val);
}

void ACharacterBase::MouseRightPressed()
{
	bMouseRightHold = true;
}

void ACharacterBase::MouseRightReleased()
{
	bMouseRightHold = false;
}

void ACharacterBase::AddControllerYawInput(float val)
{
	if (val == 0 || bMouseRightHold == false)
	{
		return;
	}
	Super::AddControllerYawInput(val);
}

void ACharacterBase::AddControllerPitchInput(float val)
{
	if (val == 0 || bMouseRightHold == false)
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
		CancelMoveToCursor();
		if (hitResult.GetActor()->GetComponentsCollisionResponseToChannel(CursorTraceChannel) == ECollisionResponse::ECR_Block)
		{
			FActorSpawnParameters parameters;
			parameters.Owner = this;
			currCursorDecal = GetWorld()->SpawnActor<ACursorDecal>(cursorDecal, hitResult.Location,
			                                                       FRotator::ZeroRotator,
			                                                       parameters);
			SetNewMoveDestination(hitResult.Location);
		}
	}
}

void ACharacterBase::SetNewMoveDestination(const FVector& desLocation)
{
	const float dist = FVector::Dist(desLocation, GetActorLocation());
	if (dist >= canMoveDistance)
	{
		bMouseMoving = true;
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(playerController, desLocation);
	}
}

void ACharacterBase::CameraZoomIn()
{
	cameraBoom->TargetArmLength = FMath::Max(cameraBoom->TargetArmLength - camerZoomStep, minCameraZoom);
}

void ACharacterBase::CameraZoomOut()
{
	cameraBoom->TargetArmLength = FMath::Min(cameraBoom->TargetArmLength + camerZoomStep, maxCameraZoom);
}

void ACharacterBase::OnAnyKeyPressed(FKey key)
{
	if (bCanFindKey)
	{
		bCanFindKey = false;
		for (auto& hotkey : mainUI->GetAllHotKeySlots())
		{
			// if (playerController->IsInputKeyDown(hotkey->key))
			if (key == hotkey->key)
			{
				if (hotkey->assignedSpell)
				{
					hotkey->assignedSpell->OnTryCastSpell();
					break;
				}
			}
		}
		bCanFindKey = true;
	}
}


void ACharacterBase::ChangeCurrentHP(float deltaHP)
{
	currentHp = FMath::Clamp(currentHp + deltaHP, 0.0f, totalHp);
	mainUI->SetHpProgressBar(currentHp / totalHp);
}

void ACharacterBase::ChangeCurrentMP(float deltaMp)
{
	currentMp = FMath::Clamp(currentMp + deltaMp, 0.0f, totalMp);
	mainUI->SetMpProgressBar(currentMp / totalMp);
}

void ACharacterBase::ChangeCurrentExp(float deltaExp)
{
	currentExp += deltaExp;
}

void ACharacterBase::SetLevel(int val)
{
	currentLevel = val;
	mainUI->SetLevelText(FText::AsNumber(currentLevel));
}

void ACharacterBase::CancelMoveToCursor()
{
	bMouseMoving = false;
	GetCharacterMovement()->StopMovementImmediately();
	if (currCursorDecal && IsValid(currCursorDecal))
	{
		currCursorDecal->Destroy();
		currCursorDecal = nullptr;
	}
}

void ACharacterBase::ReadData()
{
	UDataTable* characterInfo = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(),NULL,
	                                                              TEXT(
		                                                              "DataTable'/Game/Blueprints/Info/CharacterInfoDataTable.CharacterInfoDataTable'")));
	if (characterInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterInfo is not find!"));
		return;
	}

	FCharacterInfo* row = characterInfo->FindRow<FCharacterInfo>(TEXT("S1"),TEXT("LookupCharacterInfo"));

	if (row)
	{
		SetCharacterName(row->characterName);
		totalHp = row->startHp;
		currentHp = totalHp;
		totalMp = row->startMp;
		currentMp = totalMp;
	}
}

void ACharacterBase::UpdatePlayerDataUI()
{
	mainUI->SetLevelText(FText::AsNumber(currentLevel));
	mainUI->SetHpProgressBar(currentHp / totalHp);
	mainUI->SetMpProgressBar(currentMp / totalMp);
}

void ACharacterBase::GenerateStartingSkills()
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	params.Owner = this;
	TArray<UUI_SkillHotkey*> emptyHotkeys;

	for (const auto& hotkey : mainUI->GetAllHotKeySlots())
	{
		if (hotkey && hotkey->assignedSpell == nullptr)
		{
			int index = 0;
			for (auto& temp : emptyHotkeys)
			{
				if (hotkey->hotkeyRow > temp->hotkeyRow)
				{
					break;
				}
				if (hotkey->hotkeyRow == temp->hotkeyRow && hotkey->hotkeyIndex < temp->hotkeyIndex)
				{
					break;
				}
				index++;
			}
			emptyHotkeys.Insert(hotkey, index);
		}
	}

	for (auto& skill : startingSkills)
	{
		ASkillBase* tempSkill = GetWorld()->SpawnActor<ASkillBase>(skill, params);
		if (emptyHotkeys.Num() > 0)
		{
			const auto hotkey = emptyHotkeys[0];
			emptyHotkeys.RemoveAt(0);
			hotkey->SetAssignSpell(tempSkill);
		}
	}
}

void ACharacterBase::BeginSpellCast(ASkillBase* skill)
{
	bIsCasting = true;
	currentSkill = skill;
	for (auto& hotkeySlot : mainUI->GetAllHotKeySlots())
	{
		if (hotkeySlot->assignedSpell)
		{
			if (currentSkill == hotkeySlot->assignedSpell)
			{
				hotkeySlot->DisableHotkey();
			}
		}
	}
}

void ACharacterBase::EndSpellCast(ASkillBase* skill)
{
	bIsCasting = false;
	currentSkill = skill;
	for (auto& HotkeySlot : mainUI->GetAllHotKeySlots())
	{
		if (HotkeySlot->assignedSpell)
		{
			if (currentSkill == HotkeySlot->assignedSpell)
			{
				HotkeySlot->EnableHotkey();
			}
		}
	}
}

void ACharacterBase::OnReceiveDamage(float attackerDamage, int attackerCritChance, EAttackDamageType type, TSubclassOf<AElementBase> attackElement, AActor* attacker, ASkillBase* skill)
{
	// if (!UStaticLibrary::IsEnemy(attacker))
	// {
	// 	return;
	// }

	ChangeCurrentHP(-1 * UStaticLibrary::CalculateFinalDamage(attackerDamage, attackerCritChance, attackElement, this->element));
}
