// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCBase.h"
#include "NPC_Merchant.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API ANPC_Merchant : public ANPCBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Item")
	TArray<TSubclassOf<class AItemBase>> offeredItems;

	class ACharacterBase* playerChar;

	class UUI_Shop* shopWidget;
	
public:

	virtual void BeginPlay() override;
	
	virtual void OnInteractWith(ACharacterBase* character) override;

	virtual void OnLeavePlayerRadius(ACharacterBase* character) override;
};
