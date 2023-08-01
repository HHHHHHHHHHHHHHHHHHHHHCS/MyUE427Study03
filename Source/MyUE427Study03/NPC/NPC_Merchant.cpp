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
	auto cls = LoadClass<UUI_Shop>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_Shop.UI_Shop_C'"));
	shopWidget = CreateWidget<UUI_Shop>(GetWorld(), cls);
	shopWidget->AddToViewport(3);
	shopWidget->SetVisibility(ESlateVisibility::Hidden);
	shopWidget->SetDesiredSizeInViewport(FVector2D(500, 700));
	shopWidget->SetAnchorsInViewport(FAnchors(0.5, 0.5, 0.5, 0.5));
	shopWidget->SetAlignmentInViewport(FVector2D(0.5, 0.5));
}

void ANPC_Merchant::OnInteractWith(ACharacterBase* character)
{
	if (shopWidget->Visibility == ESlateVisibility::Visible)
	{
		shopWidget->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	shopWidget->merchant = this;
	shopWidget->playerChar = playerChar;
	shopWidget->UI_SellItem->inventoryRef = playerChar->inventoryRef;
	shopWidget->UI_SellItem->shopWidget = shopWidget;

	shopWidget->UpdateCoin();
	shopWidget->GenerateItemList();


	shopWidget->SetVisibility(ESlateVisibility::Visible);
}

void ANPC_Merchant::OnLeavePlayerRadius(ACharacterBase* character)
{
	Super::OnLeavePlayerRadius(character);
	shopWidget->SetVisibility(ESlateVisibility::Hidden);
}
