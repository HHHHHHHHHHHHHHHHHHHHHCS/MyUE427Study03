// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_DragItem.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UUI_DragItem::OnInit(int amount, UTexture2D* icon)
{
	Text_Amount->SetText(FText::AsNumber(amount));
	Image_Icon->SetBrushFromTexture(icon);
}
