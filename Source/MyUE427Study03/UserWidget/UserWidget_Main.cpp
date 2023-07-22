// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_Main.h"

#include "SkillDragOperation.h"
#include "UI_HotkeyRow.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/OverlaySlot.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/WrapBox.h"
#include "Inventory/UI_CraftMenu.h"
#include "Inventory/UI_ItemDragDropOperation.h"
#include "Inventory/UI_ItemObtain.h"
#include "Inventory/UI_Shop.h"
#include "MyUE427Study03/InventorySystem/Inventory.h"
#include "Quest/UI_Quest_Journal.h"
#include "Quest/UI_Quest_Quest.h"
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

	mainTreeRef = Cast<UUI_SkillTree_MainTree>(GetWidgetFromName("SkillTree_MainTree"));

	questListSizeBox = Cast<USizeBox>(GetWidgetFromName("SizeBox_QuestList"));

	questList = Cast<UScrollBox>(GetWidgetFromName("ScrollBox_QuestList"));

	minimapWidget = Cast<UUI_Minimap>(GetWidgetFromName("UI_Minimap"));

	questJournal = Cast<UUI_Quest_Journal>(GetWidgetFromName("QuestJournal"));

	questButton = Cast<UButton>(GetWidgetFromName("Button_Quest"));
	questButton->OnClicked.AddDynamic(this, &UUserWidget_Main::OnQuestButtonClicked);

	skillButton = Cast<UButton>(GetWidgetFromName("Button_Skill"));
	skillButton->OnClicked.AddDynamic(this, &UUserWidget_Main::OnSkillButtonClicked);

	inventoryWidget = Cast<UUI_Inventory>(GetWidgetFromName("UI_Inventory"));

	inventoryButton = Cast<UButton>(GetWidgetFromName("Button_Inventory"));
	inventoryButton->OnClicked.AddDynamic(this, &UUserWidget_Main::OnInventoryButtonClicked);

	throwAwayWidget = Cast<UUI_ThrowAway>(GetWidgetFromName("UI_ThrowAway"));

	obtainContainer = Cast<UBorder>(GetWidgetFromName("Border_ObtainContainer"));

	readableContainer = Cast<UBorder>(GetWidgetFromName("Border_ReadableContainer"));

	craftMenuWidget = Cast<UUI_CraftMenu>(GetWidgetFromName("UI_CraftMenu"));

	shopWidget =Cast<UUI_Shop>(GetWidgetFromName("UI_Shop"));

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

	UInventoryDragDropOperation* invDragOp = Cast<UInventoryDragDropOperation>(InOperation);
	if (invDragOp)
	{
		UUserWidget* dragWidget = invDragOp->dragWidget;
		dragWidget->AddToViewport();
		//SetDesiredSizeInViewport 如果不设置这个窗口大小    默认会全屏
		dragWidget->SetDesiredSizeInViewport(FVector2D(800, 600));
		//InGeometry.AbsoluteToLocal 转换局部空间
		//要减去mouseOffset 是因为坐标零点发生了改变
		dragWidget->SetPositionInViewport(
			InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition())
			- invDragOp->mouseOffset, false);
		return true;
	}

	UUI_ItemDragDropOperation* dragDropOp = Cast<UUI_ItemDragDropOperation>(InOperation);

	if (dragDropOp)
	{
		UUI_InventorySlot* slot = dragDropOp->uiDragSlot;
		if (!slot->itemInfo.canStacked && slot->amount > 0)
		{
			inventoryWidget->inventoryRef->RemoveItemAtIndex(slot->slotIndex, 1);
		}
		else
		{
			throwAwayWidget->UpdateInfo(slot->slotIndex);
			throwAwayWidget->SetVisibility(ESlateVisibility::Visible);
			inventoryWidget->WBOX_Inventory->SetIsEnabled(false);
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

UUI_Quest_Quest* UUserWidget_Main::AddQuestToList(AQuestBase* quest)
{
	if (quest)
	{
		auto cls = LoadClass<UUI_Quest_Quest>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Quest/UI_Quest.UI_Quest_C'"));
		UUI_Quest_Quest* tempQuest = CreateWidget<UUI_Quest_Quest>(GetWorld(), cls);
		tempQuest->questManager = questManager;
		tempQuest->assignedQuest = quest;
		questWidgetArray.Add(tempQuest);

		UScrollBoxSlot* temp = Cast<UScrollBoxSlot>(questList->AddChild(tempQuest));
		temp->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		temp->SetPadding(FMargin(0, 8, 0, 0));
		return tempQuest;
	}
	else
	{
		return nullptr;
	}
}

void UUserWidget_Main::OnQuestButtonClicked()
{
	if (bQuestUIVisibility)
	{
		questJournal->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		questJournal->SetVisibility(ESlateVisibility::Visible);
	}
	bQuestUIVisibility = !bQuestUIVisibility;
}

void UUserWidget_Main::OnSkillButtonClicked()
{
	if (bSkillTreeShow)
	{
		mainTreeRef->SetVisibility(ESlateVisibility::Hidden);
		bSkillTreeShow = false;
	}
	else
	{
		mainTreeRef->SetVisibility(ESlateVisibility::Visible);
		bSkillTreeShow = true;
	}
}

void UUserWidget_Main::OnInventoryButtonClicked()
{
	inventoryWidget->ToggleVisibility();
}

void UUserWidget_Main::AddItemToObtainedQueue(TSubclassOf<AItemBase> itemCls, int amount)
{
	if (!obtainedItemQueue.IsEmpty())
	{
		obtainedItemQueue.Enqueue(FInventorySlot{itemCls, amount});
	}
	else
	{
		auto obtainCls = LoadClass<UUI_ItemObtain>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_ItemObtain.UI_ItemObtain_C'"));
		UUI_ItemObtain* itemObtain = CreateWidget<UUI_ItemObtain>(GetWorld(), obtainCls);
		itemObtain->OnInit(itemCls, amount, this);
		obtainContainer->AddChild(itemObtain);
		obtainedItemQueue.Enqueue(FInventorySlot{itemCls, amount});
	}
}

void UUserWidget_Main::OnObtainMessageEnd()
{
	obtainedItemQueue.Pop();
	obtainContainer->ClearChildren();
	if (!obtainedItemQueue.IsEmpty())
	{
		auto obtainCls = LoadClass<UUI_ItemObtain>(GetWorld(), TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/Inventory/UI_ItemObtain.UI_ItemObtain_C'"));
		UUI_ItemObtain* itemObtain = CreateWidget<UUI_ItemObtain>(GetWorld(), obtainCls);
		FInventorySlot slot;
		obtainedItemQueue.Peek(slot);
		itemObtain->OnInit(slot.itemClass, slot.amount, this);
		obtainContainer->AddChild(itemObtain);
	}
}
