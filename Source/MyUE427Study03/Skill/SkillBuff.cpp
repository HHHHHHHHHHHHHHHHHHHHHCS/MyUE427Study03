// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBuff.h"

#include "MyUE427Study03/Characters/CharacterBase.h"

void ASkillBuff::ApplyEffect(float deltaTime)
{
}

void ASkillBuff::RemoveEffect()
{
}

void ASkillBuff::RestBuff()
{
	GetWorldTimerManager().ClearTimer(timerHandle_UpdateEffect);
	OnActive();
}

void ASkillBuff::OnActive()
{
	buffWidgetRef = playerReference->AddBuff(this);
	buffDuration = GetCurrentStage().castingTime;
	remainingTime = buffDuration;
	buffWidgetRef->Image_RemainingTime->SetVisibility(ESlateVisibility::Visible);
	buffWidgetRef->Text_RemaingTime->SetVisibility(ESlateVisibility::Visible);
	GetWorldTimerManager().SetTimer(timerHandle_UpdateEffect, this, &ASkillBuff::OnUpdateBuff, K_DELTA_TIME, true);
}

void ASkillBuff::OnDeActive()
{
	RemoveEffect();
	playerReference->RemoveBuff(this);
	buffWidgetRef = nullptr;
}

void ASkillBuff::OnUpdateBuff()
{
	if (remainingTime <= 0)
	{
		GetWorldTimerManager().ClearTimer(timerHandle_UpdateEffect);
		OnDeActive();
	}
	else
	{
		ApplyEffect(K_DELTA_TIME);
		remainingTime -= K_DELTA_TIME;
		FNumberFormattingOptions format;
		format.MinimumFractionalDigits = 2;
		format.MaximumFractionalDigits = 2;
		buffWidgetRef->Text_RemaingTime->SetText(FText::AsNumber(remainingTime, &format));
		buffWidgetRef->cooldownMat->SetScalarParameterValue("Percent", remainingTime / buffDuration);
	}
}

void ASkillBuff::OnSkillNotify()
{
	Super::OnSkillNotify();
	if (playerReference->buffArray.Contains(this))
	{
		RestBuff();
	}
	else
	{
		OnActive();
	}
}
