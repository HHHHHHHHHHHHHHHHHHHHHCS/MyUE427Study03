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
	constexpr static int ROW_NUM = 7;

public:
	int amountOfSlots; //插槽的数量

	int maxStackSize; //一个插槽最多的数量

	class ACharacterBase* playerChar;

	TArray<FInventorySlot> slots;

	float currentWeight;

	UPROPERTY(EditAnywhere, Category="InventoryInfo")
	float totalWeight;

	bool isOverload;

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

	UFUNCTION(BlueprintCallable)
	bool RemoveItemAtIndex(int index, int amount);

	UFUNCTION(BlueprintCallable)
	bool SwapSlot(int index1, int index2);

	UFUNCTION(BlueprintCallable)
	bool SplitStack(int index, int amount);

	UFUNCTION(BlueprintCallable)
	void UseItemAtIndex(int index);

	void UpdateActionMenuPosition(class UUI_InventorySlot* slot);

	bool AddToIndex(int fromIndex, int toIndex);

	bool SplitStackToIndex(int fromIndex, int toIndex, int amount);

	void SortInventory(ESortType type, bool isReversed);

	TArray<FInventorySlot> FindExistSlots();

	TArray<FInventorySlot> BubbleSortArray(TArray<FInventorySlot> inputArray, ESortType type, bool isReversed);

	void UpdateWeight();

	void AddWeight(float weight);

	void RemoveWeight(float weight);

	void AddWeightForItem(TSubclassOf<AItemBase> item, int amount);

	void RemoveWeightForItem(TSubclassOf<AItemBase> item, int amount);
};
