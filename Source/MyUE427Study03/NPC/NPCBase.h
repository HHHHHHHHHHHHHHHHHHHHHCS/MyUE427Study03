// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "PaperSpriteComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "MyUE427Study03/Quest/QuestBase.h"
#include "NPCBase.generated.h"

UCLASS()
class MYUE427STUDY03_API ANPCBase : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* interactionWidget;

	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* questIcon;

	UPROPERTY(EditAnywhere, Category="Quest")
	FText name;

	UPROPERTY(EditAnywhere, Category="Quest")
	TSubclassOf<class AQuestBase> myQuest;

	UPROPERTY(EditAnywhere, Category="Quest")
	bool bHasQuest;
public:
	// Sets default values for this character's properties
	ANPCBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnEnterPlayerRadius(class ACharacterBase* character) override;

	virtual void OnLeavePlayerRadius(class ACharacterBase* character) override;

	virtual void OnInteractWith(class ACharacterBase* character) override;
};
