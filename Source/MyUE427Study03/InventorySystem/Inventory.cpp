// Fill out your copyright notice in the Description page of Project Settings.
#include "Inventory.h"
#include "ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "MyUE427Study03/Characters/CharacterBase.h"
#include "MyUE427Study03/UserWidget/Inventory/UI_CraftMenu.h"
#include "MyUE427Study03/UserWidget/Inventory/UI_InventoryActionMenu.h"

// Sets default values
AInventory::AInventory()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	amountOfSlots = 40;
	maxStackSize = 99;
	totalWeight = 250;
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
					int amount = FMath::Min(remainder, maxStackSize);
					slots[idx] = FInventorySlot{item, amount};
					AddWeightForItem(item, amount);
					UpdateCraftMenu();
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
				AddWeightForItem(item, diff);
				slots[idx] = FInventorySlot{item, old + FMath::Min(remainder, diff)};
				UpdateCraftMenu();
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
			AddWeightForItem(item, amount);
			UpdateCraftMenu();
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
			RemoveWeightForItem(slots[index].itemClass, GetAmountAtIndex(index));
			slots[index] = FInventorySlot{nullptr, 0};
		}
		else
		{
			RemoveWeightForItem(slots[index].itemClass, amount);
			slots[index] = FInventorySlot{slots[index].itemClass, oldAmount - amount};
		}
		UpdateCraftMenu();
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

void AInventory::UseItemAtIndex(int index)
{
	if (slots[index].itemClass)
	{
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AItemBase* item = GetWorld()->SpawnActor<AItemBase>(slots[index].itemClass, params);
		item->inventoryRef = this;
		item->index = index;
		if (item->itemInfo.category == EItemCategories::Equipment)
		{
			item->boxCollisionComp->SetGenerateOverlapEvents(false);
		}
		item->OnUsed();
	}
}

void AInventory::UpdateActionMenuPosition(UUI_InventorySlot* slot)
{
	int x = slot->slotIndex % ROW_NUM;
	int y = slot->slotIndex / ROW_NUM;
	auto actionMenu = playerChar->mainUI->inventoryWidget->actionMenu;
	actionMenu->UpdateInfo(slot->slotIndex);
	actionMenu->SetRenderTranslation(FVector2D(x * 93, y * 93));
	actionMenu->SetVisibility(ESlateVisibility::Visible);
}

bool AInventory::AddToIndex(int fromIndex, int toIndex)
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

bool AInventory::SplitStackToIndex(int fromIndex, int toIndex, int amount)
{
	if (!IsSlotEmpty(fromIndex) && IsSlotEmpty(toIndex)
		&& GetItemByIndex(fromIndex)->itemInfo.canStacked
		&& GetAmountAtIndex(fromIndex) > amount
		&& amount > 0)
	{
		slots[fromIndex] = FInventorySlot{slots[fromIndex].itemClass, GetAmountAtIndex(fromIndex) - amount};
		slots[toIndex] = FInventorySlot{slots[fromIndex].itemClass, amount};
		UpdateSlotByIndex(fromIndex);
		UpdateSlotByIndex(toIndex);
		return true;
	}
	return false;
}

void AInventory::SortInventory(ESortType type, bool isReversed)
{
	slots = FindExistSlots();
	if (slots.Num() <= 1)
	{
		slots.SetNum(amountOfSlots);
		for (int i = 0; i < slots.Num(); i++)
		{
			UpdateSlotByIndex(i);
		}
		return;
	}
	slots = BubbleSortArray(slots, type, isReversed);
	slots.SetNum(amountOfSlots);
	for (int i = 0; i < slots.Num(); i++)
	{
		UpdateSlotByIndex(i);
	}
}

TArray<FInventorySlot> AInventory::FindExistSlots()
{
	TArray<FInventorySlot> tempSlots;
	for (auto slot : slots)
	{
		if (slot.itemClass)
		{
			tempSlots.Add(slot);
		}
	}
	return tempSlots;
}

TArray<FInventorySlot> AInventory::BubbleSortArray(TArray<FInventorySlot> inputArray, ESortType type, bool isReversed)
{
	TArray<FInventorySlot> tempSlots = inputArray;


	for (int end = tempSlots.Num() - 1; end > 0; end--)
	{
		for (int i = 0; i < end; i++)
		{
			if (type == ESortType::Category)
			{
				if ((!isReversed && tempSlots[i].itemClass.GetDefaultObject()->itemInfo.category
						> tempSlots[i + 1].itemClass.GetDefaultObject()->itemInfo.category)
					|| (isReversed && tempSlots[i].itemClass.GetDefaultObject()->itemInfo.category
						< tempSlots[i + 1].itemClass.GetDefaultObject()->itemInfo.category))
				{
					std::swap(tempSlots[i], tempSlots[i + 1]);
				}
			}
			else if (type == ESortType::Amount)
			{
				if ((!isReversed && tempSlots[i].amount > tempSlots[i + 1].amount)
					|| (isReversed && tempSlots[i].amount < tempSlots[i + 1].amount))
				{
					std::swap(tempSlots[i], tempSlots[i + 1]);
				}
			}
			else if (type == ESortType::Name)
			{
				if ((!isReversed && tempSlots[i].itemClass.GetDefaultObject()->itemInfo.name.CompareTo(
						tempSlots[i + 1].itemClass.GetDefaultObject()->itemInfo.name))
					|| (isReversed && !tempSlots[i].itemClass.GetDefaultObject()->itemInfo.name.CompareTo(
						tempSlots[i + 1].itemClass.GetDefaultObject()->itemInfo.name)))
				{
					std::swap(tempSlots[i], tempSlots[i + 1]);
				}
			}
		}
	}

	return tempSlots;
}

void AInventory::UpdateWeight()
{
	playerChar->mainUI->inventoryWidget->UpdateWeight(currentWeight, totalWeight);
}

void AInventory::AddWeight(float weight)
{
	currentWeight += weight;
	UpdateWeight();
	if (!isOverload && currentWeight > totalWeight)
	{
		isOverload = true;
		playerChar->OnOverloaded();
	}
}

void AInventory::RemoveWeight(float weight)
{
	currentWeight -= weight;
	UpdateWeight();
	if (isOverload && currentWeight <= totalWeight)
	{
		isOverload = false;
		playerChar->OnOverloadEnd();
	}
}

void AInventory::AddWeightForItem(TSubclassOf<AItemBase> item, int amount)
{
	AddWeight(item->GetDefaultObject<AItemBase>()->itemInfo.weight * amount);
}

void AInventory::RemoveWeightForItem(TSubclassOf<AItemBase> item, int amount)
{
	RemoveWeight(item->GetDefaultObject<AItemBase>()->itemInfo.weight * amount);
}

int AInventory::GetTotalAmountOfItem(TSubclassOf<AItemBase> item, TArray<int>& itemSlotIdx)
{
	int tempAmount = 0;
	for (int i = 0; i < slots.Num(); i++)
	{
		if (slots[i].itemClass && slots[i].itemClass == item)
		{
			tempAmount += slots[i].amount;
			itemSlotIdx.Add(i);
		}
	}
	return tempAmount;
}

bool AInventory::RemoveItem(TSubclassOf<AItemBase> item, int amount)
{
	TArray<int> itemArray;
	int totalAmount = GetTotalAmountOfItem(item, itemArray);

	if (totalAmount < amount)
	{
		return false;
	}

	int tempAmount = amount;
	for (int i = 0; i < itemArray.Num(); i++)
	{
		int idx = itemArray[i];
		auto temp = slots[idx];
		int oldAmount = temp.amount;
		if (temp.amount > tempAmount)
		{
			RemoveItemAtIndex(idx, tempAmount);
			RemoveWeightForItem(item, tempAmount);
			tempAmount = 0;
		}
		else
		{
			RemoveItemAtIndex(idx, oldAmount);
			RemoveWeightForItem(item, oldAmount);
			tempAmount -= oldAmount;
		}

		if (tempAmount <= 0)
		{
			break;
		}
	}

	UpdateCraftMenu();
	return true;
}

void AInventory::UpdateCraftMenu()
{
	auto item = playerChar->mainUI->craftMenuWidget->currentItem;
	if (item)
	{
		playerChar->mainUI->craftMenuWidget->UpdateDetailWindow(item);
	}
}

void AInventory::SaveGame()
{
	if (!inventorySaveInst)
	{
		inventorySaveInst = Cast<UInventorySave>(UGameplayStatics::CreateSaveGameObject(UInventorySave::StaticClass()));
	}

	inventorySaveInst->saveWeight = currentWeight;
	inventorySaveInst->savedSlots = slots;
	inventorySaveInst->SavedPickups = lootedPickups;

	UGameplayStatics::SaveGameToSlot(inventorySaveInst, savedSlotName, 0);
}

bool AInventory::IsContainsID(int itemID, int& rest)
{
	for (auto& item : lootedPickups)
	{
		if (item.id == itemID)
		{
			rest = item.restAmount;
			return true;
		}
	}
	return false;
}

void AInventory::LoadPickups()
{
	TArray<AActor*> founderActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemBase::StaticClass(), founderActors);

	for (AActor* actor : founderActors)
	{
		AItemBase* item = Cast<AItemBase>(actor);
		if (item)
		{
			if (item->id >= 0)
			{
				int restAmount;
				if (IsContainsID(item->id, restAmount))
				{
					if(restAmount>0)
					{
						item->amount = restAmount;
					}
					else
					{
						item->Destroy();
					}
				}
			}
		}
	}
}
