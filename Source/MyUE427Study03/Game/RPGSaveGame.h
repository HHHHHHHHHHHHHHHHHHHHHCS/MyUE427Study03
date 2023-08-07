// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RPGSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API URPGSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	FString savedName;
	float savedHp;
	float savedMp;
	int savedExp;
	int savedLevel;
	int savedCoin;
};
