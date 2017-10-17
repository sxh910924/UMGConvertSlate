// Fill out your copyright notice in the Description page of Project Settings.

#include "ToSWidget.h"
#include "StrAssembleLib.h"

void UToSWidget::GenerateHead(UWidget* NewWidget)
{
	ThisWidget = NewWidget;
	if (ToSWidgetClassName.IsEmpty())
	{
		// error
	}
	else
	{
		HeadString = UStrAssembleLib::Str_SNew(ToSWidgetClassName);
	}
}

void UToSWidget::GenerateWidgetProperty()
{
	ESlateVisibility vis = ThisWidget->GetVisibility();
	if (vis != ToSWidgetDefaultVisibility)
	{
		WidgetProperty.Add(UStrAssembleLib::Str_Visibility(vis));
	}
}

int32 UToSWidget::GetPanalWidgetChildrenCount() const
{
	UPanelWidget* panel = Cast<UPanelWidget>(ThisWidget);
	if (panel)
	{
		return panel->GetChildrenCount();
	}
	else
	{
		return 0;
	}
}

void UToSWidget::AddSlotProperty(const int32 SlotIndex, const TArray<FString> PropertyArr)
{
	if (PropertyArr.Num() == 0) return;
	const bool exist = this->SlotProperty.Contains(SlotIndex);
	if (exist)
	{
		SlotProperty[SlotIndex] += PropertyArr;
	}
	else
	{
		SlotProperty.Emplace(SlotIndex, PropertyArr);
	}
}

void UToSWidget::AddSlotProperty(const int32 SlotIndex, const FString &PropertyValue)
{
	const bool exist = this->SlotProperty.Contains(SlotIndex);
	if (exist)
	{
		SlotProperty[SlotIndex].Add(PropertyValue);
	}
	else
	{
		TArray<FString> firstArr;
		firstArr.Add(PropertyValue);
		SlotProperty.Emplace(SlotIndex, firstArr);
	}
}

void UToSWidget::LoopPanelSlot()
{
	for (int32 loop = 0; loop < ChildSlotCount; ++loop)
	{
		PanelSlotLoop.ExecuteIfBound(loop);
	}
}
