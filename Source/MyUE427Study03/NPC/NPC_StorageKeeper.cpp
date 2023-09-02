// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_StorageKeeper.h"

#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/UserWidget/UI_Settings.h"

void ANPC_StorageKeeper::OnInteractWith(ACharacterBase* character)
{
	character->mainUI->settingsWidget->SetVisibility(ESlateVisibility::Visible);
}

void ANPC_StorageKeeper::OnLeavePlayerRadius(ACharacterBase* character)
{
	character->mainUI->settingsWidget->SetVisibility(ESlateVisibility::Hidden);
}
