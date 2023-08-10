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
	UPROPERTY()
	FString savedName;

	UPROPERTY()
	float savedHp;

	UPROPERTY()
	float totalHp;
	
	UPROPERTY()
	float savedMp;

	UPROPERTY()
	float totalMp;
	
	UPROPERTY()
	int savedExp;

	UPROPERTY()
	int savedLevel;

	UPROPERTY()
	int savedCoin;
};
