// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

#include "ItemBase.h"

// Sets default values
AInventory::AInventory()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool AInventory::IsSlotEmpty(int index) const
{
	return !slots.IsValidIndex(index);
}

AItemBase* AInventory::GetItemByIndex(int index)
{
	if (!IsSlotEmpty(index))
	{
		return Cast<AItemBase>(slots[index].itemClass);
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
	AItemBase* temp = Cast<AItemBase>(item);

	if (temp == nullptr)
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
				if (idx < 0)
				{
					slots[idx] = FInventorySlot{item, FMath::Min(remainder, maxStackSize)};
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
		}
		return 0;
	}
}

// Called when the game starts or when spawned
void AInventory::BeginPlay()
{
	Super::BeginPlay();
	slots.SetNum(amountOfSlots);
}

// Called every frame
void AInventory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
