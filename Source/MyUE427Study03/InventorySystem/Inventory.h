// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryStruct.h"
#include "GameFramework/Actor.h"
#include "Inventory.generated.h"

UCLASS()
class MYUE427STUDY03_API AInventory : public AActor
{
	GENERATED_BODY()

public:
	int amountOfSlots; //插槽的数量

	int maxStackSize; //一个插槽最多的数量

	class ACharacterBase* playerChar;

	TArray<FInventorySlot> slots;


public:
	// Sets default values for this actor's properties
	AInventory();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	bool IsSlotEmpty(int index) const;

	AItemBase* GetItemByIndex(int index);

	int SearchEmptySlot();

	int SearchFreeStack(TSubclassOf<class AItemBase> item);

	//返回的是剩下的数量
	int AddItem(TSubclassOf<AItemBase>, int amount);

	void UpdateSlotByIndex(int index);

	int GetAmountAtIndex(int index);

	bool RemoveItemAtIndex(int index, int amount);

	bool SwapSlot(int index1, int index2);

	bool SplitStack(int index, int amount);

	void UseItemAtIndex(int index);
};
