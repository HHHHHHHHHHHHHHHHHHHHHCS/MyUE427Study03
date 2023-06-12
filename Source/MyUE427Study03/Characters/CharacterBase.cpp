// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "CharacterInfo.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/DataTable.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyUE427Study03/MyUE427Study03.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "MyUE427Study03/InventorySystem/ItemStaff.h"
#include "MyUE427Study03/Others/StaticLibrary.h"
#include "MyUE427Study03/NPC/InteractionInterface.h"
#include "MyUE427Study03/NPC/NPCBase.h"
#include "MyUE427Study03/Skill/SkillBase.h"
#include "MyUE427Study03/Skill/SkillEnum.h"
#include "MyUE427Study03/UserWidget/UserWidget_Main.h"
#include "MyUE427Study03/Skill/SkillBuff.h"
#include "MyUE427Study03/UserWidget/Inventory/UI_InventoryActionMenu.h"
#include "MyUE427Study03/UserWidget/Quest/UI_QuestList_Entry.h"
#include "MyUE427Study03/UserWidget/Quest/UI_Quest_Journal.h"

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
	cameraZoomStep = 25.0f;

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

	interactionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractionComp"));
	interactionComp->SetupAttachment(RootComponent);
	interactionComp->SetRelativeLocation(FVector(120, 0, 0));
	interactionComp->SetRelativeRotation(FRotator(90, 0, 0));
	interactionComp->SetCapsuleHalfHeight(220.0f);
	interactionComp->SetCapsuleRadius(100.0f);
	interactionComp->OnComponentBeginOverlap.AddDynamic(this, &ACharacterBase::OnInteractionCompBeginOverlap);
	interactionComp->OnComponentEndOverlap.AddDynamic(this, &ACharacterBase::OnInteractionCompEndOverlap);

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

	skillTreeComp = CreateDefaultSubobject<USkillTreeComponent>(TEXT("SkillTreeComp"));

	defaultSpeed = GetCharacterMovement()->GetMaxSpeed();
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	params.Owner = this;

	playerController = Cast<APlayerController>(GetController());
	playerController->bShowMouseCursor = true;

	inventoryRef = GetWorld()->SpawnActor<AInventory>(inventoryClass, params);

	//查找UserWidget这种 需要在路径地址末尾加_C
	mainUI = CreateWidget<UUserWidget_Main>(GetWorld(), LoadClass<UUserWidget_Main>(
		                                        this,TEXT(
			                                        "WidgetBlueprint'/Game/Blueprints/UserWidget/UI_Main.UI_Main_C'")));
	mainUI->AddToViewport();
	mainUI->GenerateHotkeys(keys, keysPerRow);
	mainUI->questManager = questManager;
	UpdatePlayerDataUI();
	// 取消初始技能的升级
	// GenerateStartingSkills();
	InCreaseLevel(0);
	IncreaseCurrentExp(0);
	skillTreeComp->SetupTree();


	questManager = GetWorld()->SpawnActor<AQuestManager>(questManagerCls, params);
	questManager->OnInit(this, mainUI);
	mainUI->questJournal->Initialize(questManager);

	mainUI->inventoryWidget->inventoryRef = inventoryRef;
	mainUI->inventoryWidget->GenerateSlotWidget();

	mainUI->inventoryWidget->actionMenu->inventoryRef = inventoryRef;
	mainUI->throwAwayWidget->inventoryRef = inventoryRef;

	inventoryRef->UpdateWeight();
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
	PlayerInputComponent->BindAction("ToggleShowSkillTree", EInputEvent::IE_Pressed, this, &ACharacterBase::ToggleShowSkillTree);
	PlayerInputComponent->BindAction("ToggleShowQuest", EInputEvent::IE_Pressed, this, &ACharacterBase::ToggleShowQuest);
	PlayerInputComponent->BindAction("Interaction", EInputEvent::IE_Pressed, this, &ACharacterBase::InteractToNPC);
	PlayerInputComponent->BindAction("PlaySlideOutAnim", EInputEvent::IE_Pressed, this, &ACharacterBase::PlaySlideOutAnim);
	PlayerInputComponent->BindAction("Inventory", EInputEvent::IE_Pressed, this, &ACharacterBase::ToggleInventory);
	PlayerInputComponent->BindAction("TestCompleteQuest", EInputEvent::IE_Pressed, this, &ACharacterBase::TestCompleteQuest);
	PlayerInputComponent->BindAction("TestFailQuest", EInputEvent::IE_Pressed, this, &ACharacterBase::TestFailQuest);
	PlayerInputComponent->BindAction("LeftShift", EInputEvent::IE_Pressed, this, &ACharacterBase::OnShiftPressed);
	PlayerInputComponent->BindAction("LeftShift", EInputEvent::IE_Released, this, &ACharacterBase::OnShiftReleased);
}

void ACharacterBase::MoveForward(float val)
{
	//val==0 也在调用
	if (val == 0 || Controller == nullptr)
	{
		return;
	}

	if (bMouseMoving)
	{
		CancelMoveToCursor();
	}

	CancelMissile();

	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(direction, val);
	questManager->OnPlayMove();
}

void ACharacterBase::MoveRight(float val)
{
	//val==0 也在调用
	if (val == 0 || Controller == nullptr)
	{
		return;
	}

	if (bMouseMoving)
	{
		CancelMoveToCursor();
	}

	CancelMissile();

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
	playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);
	if (hitResult.bBlockingHit)
	{
		CancelMoveToCursor();
		CancelMissile();

		auto selectable = Cast<ISelectableInterface>(hitResult.GetActor());
		if (selectable)
		{
			if (selectedActor == hitResult.GetActor())
			{
				//两次点击是同一个actor
				selectedActor = hitResult.GetActor();
				selectable->OnSelected(this);
			}
			else
			{
				//两次点击的是不同actor
				if (selectedActor)
				{
					Cast<ISelectableInterface>(selectedActor)->OnSelectionEnd(this);
				}
				selectable->OnSelected(this);
				selectedActor = hitResult.GetActor();
			}
		}
		else if (hitResult.GetActor()->GetComponentsCollisionResponseToChannel(CursorTraceChannel) ==
			ECollisionResponse::ECR_Block)
		{
			//点到空地 取消选择
			if (selectedActor)
			{
				Cast<ISelectableInterface>(selectedActor)->OnSelectionEnd(this);
				selectedActor = nullptr;
				return;
			}

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
		questManager->OnPlayMove();
	}
}

void ACharacterBase::CameraZoomIn()
{
	cameraBoom->TargetArmLength = FMath::Max(cameraBoom->TargetArmLength - cameraZoomStep, minCameraZoom);
}

void ACharacterBase::CameraZoomOut()
{
	cameraBoom->TargetArmLength = FMath::Min(cameraBoom->TargetArmLength + cameraZoomStep, maxCameraZoom);
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

void ACharacterBase::ToggleShowSkillTree()
{
	skillTreeComp->HandleShowCommand();
}

void ACharacterBase::ToggleShowQuest()
{
	mainUI->OnQuestButtonClicked();
}

void ACharacterBase::ToggleInventory()
{
	mainUI->OnInventoryButtonClicked();
}


void ACharacterBase::TestCompleteQuest()
{
	if (questManager->currentQuestActors.Num() > 0)
	{
		questManager->currentQuestActors[0]->OnSubGoalCompleted(0, true);
	}
}

void ACharacterBase::TestFailQuest()
{
	if (questManager->currentQuestActors.Num() > 0)
	{
		questManager->currentQuestActors[0]->OnSubGoalCompleted(1, false);
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
	if (deltaExp != 0)
	{
		currentExp += deltaExp;
		if (currentExp >= currentMaxExp)
		{
			currentExp -= currentMaxExp;
			InCreaseLevel();
		}
	}
	mainUI->SetExpPanel(currentExp, currentMaxExp);
}

void ACharacterBase::IncreaseCurrentExp(float val)
{
	ChangeCurrentExp(val);
}

void ACharacterBase::SetLevel(int val)
{
	currentLevel = val;
	currentMaxExp = FMath::FloorToInt((FMath::Pow(currentLevel - 1, 3) + 60) / 5 * ((currentLevel - 1) * 2 + 60) + 60);
	mainUI->SetLevelText(FText::AsNumber(currentLevel));
	for (UUI_QuestList_Entry* questListEntry : mainUI->questJournal->allQuestListEntries)
	{
		questListEntry->UpdateLevelColor();
	}

	if (mainUI->questJournal->currQuestListEntry)
	{
		mainUI->questJournal->UpdateSuggestedLevelColor();
	}

	UGameplayStatics::SpawnEmitterAttached(levelupParticle, GetMesh());
}

void ACharacterBase::InCreaseLevel(int val)
{
	this->SetLevel(GetCurrentLevel() + val);
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

void ACharacterBase::OnReceiveDamage(float attackerDamage, int attackerCritChance, EAttackDamageType type,
                                     TSubclassOf<AElementBase> attackElement, AActor* attacker,
                                     ASkillBase* skill)
{
	// if (!UStaticLibrary::IsEnemy(attacker))
	// {
	// 	return;
	// }

	ChangeCurrentHP(
		-1 * UStaticLibrary::CalculateFinalDamage(attackerDamage, attackerCritChance, attackElement, this->element));
}

void ACharacterBase::CancelMissile()
{
	if (sKillMissile)
	{
		// GetCharacterMovement()->DisableMovement();
		GetMovementComponent()->StopMovementImmediately();
		sKillMissile->StopCalcDist();
	}
}


UUI_BuffWidget* ACharacterBase::AddBuff(ASkillBuff* skillBuff)
{
	if (buffArray.Contains(skillBuff))
	{
		return skillBuff->buffWidgetRef;
	}

	buffArray.Add(skillBuff);
	auto cls = LoadClass<UUI_BuffWidget>(
		GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Skill/UI_Buff.UI_Buff_C'"));
	UUI_BuffWidget* buffWidget = CreateWidget<UUI_BuffWidget>(GetWorld(), cls);
	buffWidget->buffTexure = skillBuff->buffIcon;
	mainUI->buffBox->AddChildToHorizontalBox(buffWidget);
	return buffWidget;
}

void ACharacterBase::RemoveBuff(ASkillBuff* skillBuff)
{
	if (!buffArray.Contains(skillBuff))
	{
		return;
	}

	buffArray.Remove(skillBuff);
	skillBuff->buffWidgetRef->RemoveFromParent();
}

void ACharacterBase::OnInteractionCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                   bool bFromSweep,
                                                   const FHitResult& SweepResult)
{
	IInteractionInterface* actor = Cast<IInteractionInterface>(OtherActor);

	if (!actor)
	{
		return;
	}

	actor->OnEnterPlayerRadius(this);
}

void ACharacterBase::OnInteractionCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IInteractionInterface* actor = Cast<IInteractionInterface>(OtherActor);

	if (!actor)
	{
		return;
	}

	actor->OnLeavePlayerRadius(this);
}

void ACharacterBase::InteractToNPC()
{
	TArray<AActor*> overlapActors;
	//TSubclassOf<ANPCBase>() 其实判断不严谨 会拿到包括所有的actor
	//如果是ANPCBase::StaticClass(), 就只有npc了
	//其实我们只用拿到class 筛选接口就好了
	interactionComp->GetOverlappingActors(overlapActors, TSubclassOf<ANPCBase>());
	for (auto item : overlapActors)
	{
		IInteractionInterface* it = Cast<IInteractionInterface>(item);
		if (it)
		{
			it->OnInteractWith(this);
			break;
		}
	}
}

void ACharacterBase::OnShiftPressed()
{
	isShiftDown = true;
}

void ACharacterBase::OnShiftReleased()
{
	isShiftDown = false;
}

bool ACharacterBase::EquipItem(AItemStaff* _staff)
{
	if (!staff)
	{
		if (inventoryRef->RemoveItemAtIndex(_staff->index, 1))
		{
			staff = _staff;
			staff->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, *staff->socketName);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (UnEquipItem())
		{
			return EquipItem(_staff);
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool ACharacterBase::UnEquipItem()
{
	if (staff)
	{
		if (inventoryRef->AddItem(staff->GetClass(), 1) <= 0)
		{
			staff->Destroy();
			staff = nullptr;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void ACharacterBase::OnOverloaded()
{
	GetCharacterMovement()->MaxWalkSpeed = defaultSpeed / 2;
}

void ACharacterBase::OnOverloadEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = defaultSpeed / 2;
}
