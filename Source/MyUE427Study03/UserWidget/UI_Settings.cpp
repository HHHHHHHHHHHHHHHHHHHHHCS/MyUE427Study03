// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Settings.h"

#include "Kismet/GameplayStatics.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "MyUE427Study03/InventorySystem/Storage.h"

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

	if (player && player->inventoryRef)
	{
		player->inventoryRef->SaveInventory();
	}

	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStorage::StaticClass(), foundActors);
	for (AActor* actor : foundActors)
	{
		AStorage* storage = Cast<AStorage>(actor);
		if(storage)
		{
			storage->SaveStorage();
		}
	}
}
