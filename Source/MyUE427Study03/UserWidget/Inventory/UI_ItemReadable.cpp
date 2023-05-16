// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_ItemReadable.h"

#include "Components/Button.h"
#include "MyUE427Study03/InventorySystem/ItemMap.h"

void UUI_ItemReadable::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Close->OnClicked.AddDynamic(this, &UUI_ItemReadable::OnCloseButtonClicked);
}

void UUI_ItemReadable::OnCloseButtonClicked()
{
	itemMap->OnReaderEnd();
}
