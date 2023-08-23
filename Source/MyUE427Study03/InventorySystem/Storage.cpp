// Fill out your copyright notice in the Description page of Project Settings.


#include "Storage.h"

#include "Kismet/GameplayStatics.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/Game/StorageSave.h"

// Sets default values
AStorage::AStorage()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	amountOfSlots = 40;
	maxStackSize = 99;
}

// Called when the game starts or when spawned
void AStorage::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStorage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int AStorage::SearchEmptySlot()
{
	for (int i = 0; i < slots.Num(); i++)
	{
		if (!slots[i].itemClass)
		{
			return i;
		}
	}
	return -1;
}

int AStorage::SearchFreeStack(TSubclassOf<AItemBase> item)
{
	for (int i = 0; i < slots.Num(); i++)
	{
		const FInventorySlot* temp = &slots[i];
		if (temp->itemClass && temp->itemClass == item
			&& temp->amount < maxStackSize)
		{
			return i;
		}
	}
	return -1;
}

int AStorage::AddItem(TSubclassOf<AItemBase> item, int amount)
{
	AItemBase* temp = Cast<AItemBase>(item->GetDefaultObject());

	if (item == nullptr)
	{
		return 0;
	}

	if (temp->itemInfo.canStacked)
	{
		int remainder = amount;

		while (remainder > 0)
		{
			//如果物品可以被堆积
			//先找可以堆积的插槽, 如果没有再给空的
			int idx = SearchFreeStack(item);
			if (idx < 0)
			{
				idx = SearchEmptySlot();
				if (idx >= 0)
				{
					int amount = FMath::Min(remainder, maxStackSize);
					slots[idx] = FInventorySlot{item, amount};
					UpdateSlotByIndex(idx);
					remainder -= amount;
				}
				else
				{
					return remainder;
				}
			}
			else
			{
				int old = slots[idx].amount;
				int diff = maxStackSize - old;
				slots[idx] = FInventorySlot{item, old + FMath::Min(remainder, diff)};
				UpdateSlotByIndex(idx);
				remainder -= diff;
			}
		}
		return 0;
	}
	else
	{
		//如果物品不能被堆积
		for (int i = 0; i < amount; i++)
		{
			int idx = SearchEmptySlot();
			if (SearchEmptySlot() < 0)
			{
				return amount - i;
			}
			//找到了空的插槽
			slots[idx] = FInventorySlot{item, 1};
			UpdateSlotByIndex(idx);
		}
		return 0;
	}
}

bool AStorage::IsSlotEmpty(int index) const
{
	return slots[index].itemClass == nullptr;
}

AItemBase* AStorage::GetItemByIndex(int index)
{
	if (!IsSlotEmpty(index))
	{
		return Cast<AItemBase>(slots[index].itemClass.GetDefaultObject());
	}
	return nullptr;
}

void AStorage::UpdateSlotByIndex(int index)
{
	playerChar->mainUI->inventoryWidget->inventorySlots[index]->UpdateSlot();
}

int AStorage::GetAmountAtIndex(int index)
{
	return slots[index].amount;
}

bool AStorage::SwapSlot(int index1, int index2)
{
	if (index1 >= slots.Num() || index2 >= slots.Num())
	{
		return false;
	}

	FInventorySlot tempSlot = slots[index1];
	slots[index1] = slots[index2];
	slots[index2] = tempSlot;
	UpdateSlotByIndex(index1);
	UpdateSlotByIndex(index2);
	return true;
}

bool AStorage::AddToIndex(int fromIndex, int toIndex)
{
	if (slots[fromIndex].itemClass == slots[toIndex].itemClass
		&& GetItemByIndex(fromIndex)->itemInfo.canStacked
		&& GetAmountAtIndex(toIndex) < maxStackSize)
	{
		int fromAmount = GetAmountAtIndex(fromIndex);
		int toAmount = GetAmountAtIndex(toIndex);
		int sumCount = fromAmount + toAmount;

		if (sumCount <= maxStackSize)
		{
			slots[toIndex] = FInventorySlot{slots[fromIndex].itemClass, (fromAmount + toAmount)};
			slots[fromIndex] = FInventorySlot{nullptr, 0};
		}
		else
		{
			slots[toIndex] = FInventorySlot{slots[fromIndex].itemClass, maxStackSize};
			slots[fromIndex] = FInventorySlot{slots[toIndex].itemClass, sumCount - maxStackSize};
		}
		UpdateSlotByIndex(fromIndex);
		UpdateSlotByIndex(toIndex);
		return true;
	}

	return false;
}

bool AStorage::RemoveItemAtIndex(int index, int amount)
{
	if (amount > 0 && !IsSlotEmpty(index))
	{
		int oldAmount = GetAmountAtIndex(index);
		if (amount >= oldAmount)
		{
			slots[index] = FInventorySlot{nullptr, 0};
		}
		else
		{
			slots[index] = FInventorySlot{slots[index].itemClass, oldAmount - amount};
		}
		UpdateSlotByIndex(index);
		return true;
	}
	else
	{
		return false;
	}
}

bool AStorage::AddItemToIndex(int index, TSubclassOf<AItemBase> item, int amount)
{
	if (IsSlotEmpty(index) && amount < maxStackSize)
	{
		slots[index] = FInventorySlot{item, amount};
		UpdateSlotByIndex(index);
		return true;
	}
	return false;
}

bool AStorage::IncreaseAmountAtIndex(int index, int amount)
{
	if (!IsSlotEmpty(index) && (GetAmountAtIndex(index) + amount) <= maxStackSize)
	{
		slots[index].amount += amount;
		UpdateSlotByIndex(index);
		return true;
	}
	return false;
}

void AStorage::OpenStorage()
{
	// TODO:
}

void AStorage::CloseStorage()
{
	// TODO:
}

bool AStorage::MoveFromInvToStorageByIndex(AInventory* inventory, int inventoryIndex, int storageIndex)
{
	// TODO:
	return true;
}

void AStorage::SaveStorage()
{
	if (!storageSaveInst)
	{
		storageSaveInst = Cast<UStorageSave>(UGameplayStatics::CreateSaveGameObject(UStorageSave::StaticClass()));
	}

	storageSaveInst->savedSlots = slots;

	UGameplayStatics::SaveGameToSlot(storageSaveInst, savedSlotName, 0);
}

void AStorage::LoadStorage()
{
	if (!storageSaveInst)
	{
		storageSaveInst = Cast<UStorageSave>(UGameplayStatics::LoadGameFromSlot(savedSlotName, 0));
	}

	slots = storageSaveInst->savedSlots;
}
