// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryStruct.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "MyUE427Study03/NPC/InteractionInterface.h"
#include "ItemBase.generated.h"

UCLASS()
class MYUE427STUDY03_API AItemBase : public AActor, public IInteractionInterface
{
private:
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemBase();

public:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* boxCollisionComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* staticMeshComp;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* interactionUI;

	UPROPERTY(EditAnywhere, Category="Item")
	FItemInfo itemInfo;

	UPROPERTY(EditAnywhere, Category="Item")
	int amount;

	UPROPERTY(EditAnywhere, Category="Item")
	int id = -1;

	int index;

	class AInventory* inventoryRef;

protected:
	int remainder;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnEnterPlayerRadius(ACharacterBase* character) override;
	virtual void OnLeavePlayerRadius(ACharacterBase* character) override;
	virtual void OnInteractWith(ACharacterBase* character) override;
	virtual void OnUsed();
};
