// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyUE427Study03/Characters/CharacterBase.h"

// Sets default values
ASkillBase::ASkillBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASkillBase::BeginPlay()
{
	Super::BeginPlay();
	playerReference = Cast<ACharacterBase>(UGameplayStatics::GetPlayerPawn(this, 0));
	animInst = playerReference->GetMesh()->GetAnimInstance();
}

// Called every frame
void ASkillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkillBase::OnTryCastSpell()
{
	if (!bIsCooldown && !bCurrCasting && !playerReference->GetBIsCasting())
	{
		InitSpellCast();
	}
}

void ASkillBase::InitSpellCast()
{
	if (playerReference->GetCurrentMP() >= GetCurrentStage().manaCost)
	{
		bCurrCasting = true;
		playerReference->ChangeCurrentMP(-GetCurrentStage().manaCost);
		playerReference->BeginSpellCast(this);
		OnSpellCast();
	}
	else
	{
		playerReference->mainUI->PlayPopupAnimation();
	}
}

void ASkillBase::OnSpellCast()
{
	UE_LOG(LogTemp, Warning, TEXT("Casting skill: %s"), *skillInfo.name.ToString());
	if (skillAnimMontage)
	{
		PlaySkillAnim(skillAnimMontage);
	}
	OnCastCompleted();
}

void ASkillBase::OnCastCompleted()
{
	playerReference->EndSpellCast(this);
	bCurrCasting = false;
	bIsCooldown = true;

	if (hotkey)
	{
		hotkey->Button_Skill->SetIsEnabled(false);
		hotkey->Image_SkillIcon->SetColorAndOpacity(FLinearColor(0.33f, 0.33f, 0.33f, 1.0f));
		hotkey->cooldownMat->SetScalarParameterValue("Percent", 1.0f);
		hotkey->Image_Cooldown->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		hotkey->Text_Cooldown->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		currCD = GetCurrentStage().cooldownTime;
		GetWorldTimerManager().SetTimer(timerHandle_cooldown, this, &ASkillBase::OnCooldown, 0.01f, true);
	}
}

void ASkillBase::OnCooldown()
{
	if (currCD <= 0)
	{
		GetWorldTimerManager().ClearTimer(timerHandle_cooldown);
		OnCooldownExpired();
	}
	else
	{
		currCD -= 0.01f;
		hotkey->cooldownMat->SetScalarParameterValue("Percent", currCD / GetCurrentStage().cooldownTime);
		if (currCD >= 1.0f)
		{
			hotkey->Text_Cooldown->SetText(FText::AsNumber(FMath::RoundHalfToZero(currCD)));
		}
		else
		{
			hotkey->Text_Cooldown->SetText(FText::AsNumber(0.1f * FMath::RoundHalfToZero(10.0f * currCD)));
		}
	}
}

void ASkillBase::OnCooldownExpired()
{
	bIsCooldown = false;
	if (hotkey)
	{
		if (hotkey->GetIsActive())
		{
			hotkey->Button_Skill->SetIsEnabled(true);
			hotkey->Image_SkillIcon->SetColorAndOpacity(FLinearColor::White);
		}

		hotkey->cooldownMat->SetScalarParameterValue("Percent", 0);
		hotkey->Image_Cooldown->SetVisibility(ESlateVisibility::Hidden);
		hotkey->Text_Cooldown->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ASkillBase::PlaySkillAnim(UAnimMontage* skillAnimMon)
{
	const auto charMove = playerReference->GetCharacterMovement();
	charMove->DisableMovement();
	charMove->StopMovementImmediately();
	animInst->Montage_Play(skillAnimMon);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetMove, this, &ASkillBase::ResetMovement,
	                                skillAnimMon->SequenceLength, false);
}

void ASkillBase::ResetMovement()
{
	playerReference->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ASkillBase::OnSkillNotify()
{
}
