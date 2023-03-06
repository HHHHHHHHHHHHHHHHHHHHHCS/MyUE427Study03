// Fill out your copyright notice in the Description page of Project Settings.
#include "Inventory.h"
#include "ItemBase.h"
#include "MyUE427Study03/Characters/CharacterBase.h"

// Sets default values
AInventory::AInventory()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	amountOfSlots = 40;
	maxStackSize = 99;
}

// Called when the game starts or when spawned
void AInventory::BeginPlay()
{
	Super::BeginPlay();
	playerChar = Cast<ACharacterBase>(GetOwner());
	slots.SetNum(amountOfSlots);
}

// Called every frame
void AInventory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AInventory::IsSlotEmpty(int index) const
{
	return slots[index].itemClass == nullptr;
}

AItemBase* AInventory::GetItemByIndex(int index)
{
	if (!IsSlotEmpty(index))
	{
		return Cast<AItemBase>(slots[index].itemClass.GetDefaultObject());
	}
	return nullptr;
}

int AInventory::SearchEmptySlot()
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

int AInventory::SearchFreeStack(TSubclassOf<AItemBase> item)
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

int AInventory::AddItem(TSubclassOf<AItemBase> item, int amount)
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
					slots[idx] = FInventorySlot{item, FMath::Min(remainder, maxStackSize)};
					UpdateSlotByIndex(idx);
					remainder -= maxStackSize;
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

void AInventory::UpdateSlotByIndex(int index)
{
	playerChar->mainUI->inventoryWidget->inventorySlots[index]->UpdateSlot();
}


int AInventory::GetAmountAtIndex(int index)
{
	return slots[index].amount;
}

bool AInventory::RemoveItemAtIndex(int index, int amount)
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

bool AInventory::SwapSlot(int index1, int index2)
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

bool AInventory::SplitStack(int index, int amount)
{
	if (IsSlotEmpty(index))
	{
		return false;
	}

	int oldAmount = GetAmountAtIndex(index);
	if (oldAmount <= amount || !GetItemByIndex(index)->itemInfo.canStacked)
	{
		return false;
	}

	int emptyIndex = SearchEmptySlot();
	if (emptyIndex < 0)
	{
		return false;
	}

	FInventorySlot tempSlot = slots[index];
	slots[index] = FInventorySlot{tempSlot.itemClass, oldAmount - amount};
	slots[emptyIndex] = FInventorySlot{tempSlot.itemClass, amount};
	UpdateSlotByIndex(index);
	UpdateSlotByIndex(emptyIndex);
	return true;
}
