// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_BuffWidget.h"

void UUI_BuffWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Image_BuffIcon->SetBrushFromTexture(buffTexure);
	cooldownMat = Image_RemainingTime->GetDynamicMaterial();
}
