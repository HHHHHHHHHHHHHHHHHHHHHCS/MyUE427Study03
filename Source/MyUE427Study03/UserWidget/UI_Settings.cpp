// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Settings.h"

#include "Kismet/GameplayStatics.h"
#include "MyUE427Study03/Characters/CharacterBase.h"

void UUI_Settings::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Save->OnClicked.AddDynamic(this, &UUI_Settings::OnSaveButtonClick);
}

void UUI_Settings::OnSaveButtonClick()
{
	if (!player)
	{
		player = Cast<ACharacterBase>(UGameplayStatics::GetPlayerPawn(this, 0));
	}
	player->SaveGame();
}
