// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Inventory.h"

#include "UI_InventoryActionMenu.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/WrapBox.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "MyUE427Study03/Others/StaticLibrary.h"

void UUI_Inventory::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Close->OnClicked.AddDynamic(this, &UUI_Inventory::OnCloseButtonClick);
	Button_Sort->OnClicked.AddDynamic(this, &UUI_Inventory::OnSortButtonClick);
	actionMenu = Cast<UUI_InventoryActionMenu>(GetWidgetFromName(TEXT("UI_InventoryActionMenu")));
	auto sortArray = UStaticLibrary::GetEnumArray<ESortType>("ESortType");
	for (auto item : sortArray)
	{
		CBox_SortCategory->AddOption(UStaticLibrary::GetEnumValueAsString("ESortType", item));
	}
	CBox_SortCategory->SetSelectedOption(CBox_SortCategory->GetOptionAtIndex(0));
}

void UUI_Inventory::GenerateSlotWidget()
{
	WBOX_Inventory->ClearChildren();
	inventorySlots.Empty();
	auto* slotCls = LoadClass<UUI_InventorySlot>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_InventorySlot.UI_InventorySlot_C'"));
	for (int i = 0; i < inventoryRef->slots.Num(); i++)
	{
		UUI_InventorySlot* slotUI = CreateWidget<UUI_InventorySlot>(GetWorld(), slotCls);
		slotUI->inventoryRef = inventoryRef;
		slotUI->slotIndex = i;
		slotUI->UpdateSlot();
		WBOX_Inventory->AddChild(slotUI);
		inventorySlots.Add(slotUI);
	}
}

void UUI_Inventory::OnCloseButtonClick()
{
	if (bInventoryShow)
	{
		SetVisibility(ESlateVisibility::Hidden);
		bInventoryShow = false;
	}
}

void UUI_Inventory::ToggleVisibility()
{
	if (bInventoryShow)
	{
		SetVisibility(ESlateVisibility::Hidden);
		bInventoryShow = false;
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
		bInventoryShow = true;
	}
}

void UUI_Inventory::OnSortButtonClick()
{
	int idx = CBox_SortCategory->FindOptionIndex(CBox_SortCategory->GetSelectedOption());
	inventoryRef->SortInventory(static_cast<ESortType>(idx), isReversed);
	isReversed = !isReversed;
}

FReply UUI_Inventory::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		dragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::RightMouseButton).NativeReply;
	}

	return FReply::Handled();
}

void UUI_Inventory::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragDropOperation* dragOp = UWidgetBlueprintLibrary::CreateDragDropOperation(inventoryDragDropOperationCls);
	dragOp->Pivot = EDragPivot::MouseDown;

	dragOp->DefaultDragVisual = this;
	OutOperation = dragOp;
	UInventoryDragDropOperation* obj = Cast<UInventoryDragDropOperation>(dragOp);
	if (obj)
	{
		obj->dragWidget = this;
		obj->mouseOffset = dragOffset;
	}
	this->RemoveFromParent();
}

void UUI_Inventory::UpdateWeight(float currWeight, float totalWeight)
{
	Text_CurrentWeight->SetText(FText::AsNumber(currWeight));
	Text_TotalWeight->SetText(FText::AsNumber(totalWeight));

	if (currWeight > totalWeight)
	{
		Text_CurrentWeight->SetColorAndOpacity(FLinearColor::Red);
		Text_TotalWeight->SetColorAndOpacity(FLinearColor::Red);
	}
	else
	{
		Text_CurrentWeight->SetColorAndOpacity(FLinearColor::White);
		Text_TotalWeight->SetColorAndOpacity(FLinearColor::White);
	}
}
