// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Storage.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "MyUE427Study03/InventorySystem/Storage.h"

void UUI_Storage::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Close->OnClicked.AddDynamic(this, &UUI_Storage::OnCloseButtonClick);
}

void UUI_Storage::GenerateSlot(AStorage* storage)
{
	storageRef = storage;
	WBOX_Storage->ClearChildren();
	storageSlotArray.Empty();
	auto* slotCls = LoadClass<UUI_StorageSlot>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_StorageSlot.UI_StorageSlot_C'"));
	for (int i = 0; i < storageRef->slots.Num(); i++)
	{
		UUI_StorageSlot* slotUI = CreateWidget<UUI_StorageSlot>(GetWorld(), slotCls);
		slotUI->storageRef = storageRef;
		slotUI->slotIndex = i;
		slotUI->UpdateSlot();
		WBOX_Storage->AddChild(slotUI);
		storageSlotArray.Add(slotUI);
	}
}

void UUI_Storage::OnCloseButtonClick()
{
	SetVisibility(ESlateVisibility::Hidden);
}
