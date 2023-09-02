// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCBase.h"
#include "NPC_StorageKeeper.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API ANPC_StorageKeeper : public ANPCBase
{
	GENERATED_BODY()

public:
	virtual void OnInteractWith(ACharacterBase* character) override;
	
	virtual void OnLeavePlayerRadius(ACharacterBase* character) override;
};
