// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SkillTree_SubTree.h"

#include "UI_SkillTree_Connection.h"
#include "UI_SkillTree_Entry.h"
#include "Components/CanvasPanelSlot.h"

void UUI_SkillTree_SubTree::NativeConstruct()
{
	Super::NativeConstruct();
	GenerateContent();
}

void UUI_SkillTree_SubTree::GenerateContent()
{
	CanvasPanel_Root->ClearChildren();
	skillEntries.Empty();
	connections.Empty();

	auto entryCls = LoadClass<UUI_SkillTree_Entry>(GetWorld(),TEXT(
		                                               "WidgetBlueprint'/Game/Blueprints/UserWidget/Skill/SkillTree/UI_SkillTree_Entry.UI_SkillTree_Entry_C'"));

	for (auto& entry : content.skills)
	{
		UUI_SkillTree_Entry* widget = CreateWidget<UUI_SkillTree_Entry>(GetWorld(), entryCls);
		widget->subTree = this;
		widget->skillClass = entry.spellClass;
		skillEntries.Add(widget);
		UCanvasPanelSlot* tempSlot = CanvasPanel_Root->AddChildToCanvas(widget);
		tempSlot->SetPosition(entry.position);
		tempSlot->SetZOrder(2);
	}

	auto connectionCls = LoadClass<UUI_SkillTree_Connection>(
		GetWorld(),TEXT(
			"WidgetBlueprint'/Game/Blueprints/UserWidget/Skill/SkillTree/UI_SkillTree_Connection.UI_SkillTree_Connection_C'"));


	for (auto& connection : content.connections)
	{
		UUI_SkillTree_Connection* widget = CreateWidget<UUI_SkillTree_Connection>(GetWorld(), connectionCls);
		widget->forSKill = connection.forSpell;
		connections.Add(widget);
		UCanvasPanelSlot* tempSlot = CanvasPanel_Root->AddChildToCanvas(widget);
		tempSlot->SetPosition(connection.position);
		tempSlot->SetSize(connection.size);
		widget->SetRenderTransform(connection.transform);
	}
}
