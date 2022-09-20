// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_Main.h"

#include "SkillDragOperation.h"
#include "UI_HotkeyRow.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/OverlaySlot.h"
#include "SkillTree/UI_SkillTree_MainTree.h"

bool UUserWidget_Main::Initialize()
{
	bool isInit = Super::Initialize();
	if (!isInit)
	{
		return false;
	}

	levelText = Cast<UTextBlock>(GetWidgetFromName("Text_Level"));
	hpProgressBar = Cast<UProgressBar>(GetWidgetFromName("ProgressBar_Hp"));
	mpProgressBar = Cast<UProgressBar>(GetWidgetFromName("ProgressBar_Mp"));
	hotkeyRowContainer = Cast<UVerticalBox>(GetWidgetFromName("HotkeyRowContainer"));

	enemyBorder = Cast<UBorder>(GetWidgetFromName("EnemyBorder"));
	enemyNameLevelText = Cast<UTextBlock>(GetWidgetFromName("Text_EnemyName"));
	enemyHpText = Cast<UTextBlock>(GetWidgetFromName("Text_EnemyHp"));
	enemyHpProgressBar = Cast<UProgressBar>(GetWidgetFromName("ProgressBar_EnemyHp"));

	buffBox = Cast<UHorizontalBox>(GetWidgetFromName("HBox_Buff"));

	expProgressBar = Cast<UProgressBar>(GetWidgetFromName("ProgressBar_Exp"));
	expCurrText = Cast<UTextBlock>(GetWidgetFromName("Text_CurrExp"));
	expMaxText = Cast<UTextBlock>(GetWidgetFromName("Text_MaxExp"));

	skillTree_MainTree = Cast<UUI_SkillTree_MainTree>(GetWidgetFromName("SkillTree_MainTree"));
	
	questListSizeBox = Cast<USizeBox>(GetWidgetFromName("SizeBox_QuestList"));

	questList = Cast<UScrollBox>(GetWidgetFromName("ScrollBox_QuestList"));

	return true;
}

void UUserWidget_Main::SetLevelText(FText text)
{
	levelText->SetText(text);
}

void UUserWidget_Main::SetHpProgressBar(float percent)
{
	hpProgressBar->SetPercent(percent);
}

void UUserWidget_Main::SetMpProgressBar(float percent)
{
	mpProgressBar->SetPercent(percent);
}

void UUserWidget_Main::GenerateHotkeys(TArray<FKey> keys, int keysPerRow)
{
	if (keys.Num() % keysPerRow != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("The num of keys is invalid!"));
		return;
	}

	UClass* cls = LoadClass<UUI_HotkeyRow>(
		GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Skill/UI_HotkeyRow.UI_HotkeyRow_C'"));
	if (cls == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UUI_HotkeyRow class not found!"));
		return;
	}

	TArray<FKey> localKeys = keys;

	if (localKeys.Num() == keysPerRow)
	{
		UUI_HotkeyRow* row = CreateWidget<UUI_HotkeyRow>(GetWorld(), cls);
		row->SetHotkeys(localKeys);
		hotkeyRowContainer->AddChildToVerticalBox(row);
		allHotkeySlots.Append(row->GenerateHotkeys(0));
	}
	else
	{
		int len = localKeys.Num() / keysPerRow;
		auto slot = Cast<UOverlaySlot>(hotkeyRowContainer->Slot);
		auto padding = slot->Padding;
		// 115 是每一个间距 
		padding.Top -= (len - 1) * 115;
		slot->SetPadding(padding);
		for (int i = 0; i < len; i++)
		{
			TArray<FKey> localModifyKeys = localKeys;
			localModifyKeys.SetNum(keysPerRow);
			UUI_HotkeyRow* row = CreateWidget<UUI_HotkeyRow>(GetWorld(), cls);
			row->SetHotkeys(localModifyKeys);
			hotkeyRowContainer->AddChildToVerticalBox(row);
			allHotkeySlots.Append(row->GenerateHotkeys(i));
			// 因为确保了被整除而且有序, 所以无所谓
			localKeys.RemoveAt(0, keysPerRow);
			// for (auto& key : localModifyKeys)
			// {
			// 	SIZE_T idx = localKeys.IndexOfByKey(key);
			// 	if (idx != INDEX_NONE)
			// 	{
			// 		localKeys.RemoveAt(idx);
			// 	}
			// }
		}
	}
}

void UUserWidget_Main::PlayPopupAnimation_Implementation()
{
}

bool UUserWidget_Main::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                    UDragDropOperation* InOperation)
{
	bool bl = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	//看似是丢掉技能, 实则是丢在主界面上
	USkillDragOperation* skillDragOp = Cast<USkillDragOperation>(InOperation);

	if (skillDragOp)
	{
		if (skillDragOp->FromHotkey)
		{
			skillDragOp->FromHotkey->ClearAssignedSpell();
		}
		return true;
	}

	return bl;
}

void UUserWidget_Main::SetExpPanel(float currExp, float maxExp)
{
	expProgressBar->SetPercent(currExp / maxExp);
	expCurrText->SetText(FText::AsNumber(currExp));
	expMaxText->SetText(FText::AsNumber(maxExp));
}
