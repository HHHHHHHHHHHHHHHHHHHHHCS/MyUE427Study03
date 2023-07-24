// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Merchant.h"

#include "Kismet/GameplayStatics.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/UserWidget/Inventory/UI_SellItem.h"
#include "MyUE427Study03/UserWidget/Inventory/UI_Shop.h"

void ANPC_Merchant::BeginPlay()
{
	Super::BeginPlay();

	playerChar = Cast<ACharacterBase>(UGameplayStatics::GetPlayerPawn(this, 0));

}

void ANPC_Merchant::OnInteractWith(ACharacterBase* character)
{
	auto cls = LoadClass<UUI_Shop>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_Shop.UI_Shop_C'"));
	shopWidget = CreateWidget<UUI_Shop>(GetWorld(), cls);

	shopWidget->merchant = this;
	shopWidget->playerChar = playerChar;
	shopWidget->UI_SellItem->inventoryRef = playerChar->inventoryRef;
	shopWidget->UI_SellItem->shopWidget = shopWidget;

	shopWidget->UpdateCoin();
	shopWidget->GenerateItemList();

	shopWidget->AddToViewport();
	shopWidget->SetDesiredSizeInViewport(FVector2D(500, 700));
}
