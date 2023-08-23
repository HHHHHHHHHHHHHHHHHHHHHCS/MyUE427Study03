// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "GameFramework/Actor.h"
#include "Storage.generated.h"

UCLASS()
class MYUE427STUDY03_API AStorage : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStorage();

public:
	int amountOfSlots; //插槽的数量

	int maxStackSize; //一个插槽最多的数量

	class ACharacterBase* playerChar;

	TArray<FInventorySlot> slots;

	bool isOverload;

	UPROPERTY(EditAnywhere, Category="Item")
	TArray<TSubclassOf<AItemBase>> craftItems;

	TArray<FSavedPickup> lootedPickups;

	class UStorageSave* storageSaveInst;

	FString savedSlotName = "StorageSave";

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	int SearchEmptySlot();

	int SearchFreeStack(TSubclassOf< AItemBase> item);
	
	//返回的是剩下的数量
	int AddItem(TSubclassOf<AItemBase>, int amount);

	bool IsSlotEmpty(int index) const;

	AItemBase* GetItemByIndex(int index);

	void UpdateSlotByIndex(int index);

	int GetAmountAtIndex(int index);

	UFUNCTION(BlueprintCallable)
	bool SwapSlot(int index1, int index2);

	bool AddToIndex(int fromIndex, int toIndex);

	UFUNCTION(BlueprintCallable)
	bool RemoveItemAtIndex(int index, int amount);

	bool AddItemToIndex(int index, TSubclassOf<AItemBase> item, int amount);

	bool IncreaseAmountAtIndex(int index, int amount);

	void OpenStorage();

	void CloseStorage();

	bool MoveFromInvToStorageByIndex(class AInventory* inventory, int inventoryIndex, int storageIndex);

	void SaveStorage();

	void LoadStorage();

};
