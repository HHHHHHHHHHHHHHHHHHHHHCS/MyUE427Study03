// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_Main.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY03_API UUserWidget_Main : public UUserWidget
{
	GENERATED_BODY()


public:
	//互相引用的问题
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player")
	class ACharacterBase* player;

public:
	UFUNCTION(BlueprintCallable)
	inline ACharacterBase* GetPlayer() const
	{
		return player;
	};
};
