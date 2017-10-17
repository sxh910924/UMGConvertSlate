// Fill out your copyright notice in the Description page of Project Settings.

#include "ToSConstraintCanvas.h"
#include "StrAssembleLib.h"
#include "SeparationLib.h"

UToSConstraintCanvas::UToSConstraintCanvas()
{
	UToSWidget::ToSWidgetClassName = FString(TEXT("SConstraintCanvas"));
	UToSWidget::ToSWidgetDefaultVisibility = ESlateVisibility::SelfHitTestInvisible;
}

void UToSConstraintCanvas::GenerateChildWidget()
{
	UToSWidget::ChildSlotCount = GetPanalWidgetChildrenCount();
	if (ChildSlotCount == 0) return;

	m_CanvasPanel = Cast<UCanvasPanel>(UToSWidget::ThisWidget);
	if (!m_CanvasPanel) return;

	// 复用循环需要做
	UToSWidget::PanelSlotLoop.BindUObject(this, &UToSConstraintCanvas::GenerateSlotProperty);
	UToSWidget::LoopPanelSlot();
}

void UToSConstraintCanvas::GenerateSlotProperty(const int32 SlotIndex)
{
	UCanvasPanelSlot* cps = Cast<UCanvasPanelSlot>(m_CanvasPanel->GetChildAt(SlotIndex)->Slot);
	if (cps)
	{
		FString slotHead = UStrAssembleLib::Str_NormalSlotHead(UToSWidget::ToSWidgetClassName);
		AddSlotProperty(SlotIndex, slotHead);
		TArray<FString> alignmentArr = UStrAssembleLib::Str_Alignment(cps->LayoutData.Alignment);
		AddSlotProperty(SlotIndex, alignmentArr);
		//cps->bAutoSize;
		//ZOrder
		TArray<FString> &slotProperty = SlotProperty[SlotIndex];
		UStrAssembleLib::Str_Final_Slot(this, slotProperty);

		UStrAssembleLib::Str_Final_SquareBracket(this, FString(TEXT("[")));

		// 处理Slot里面的对象
		UWidget* slotWidget = Cast<UWidget>(m_CanvasPanel->GetChildAt(SlotIndex));
		if (slotWidget)
		{
			USeparationLib::GenerateSlateCode(slotWidget);
		}

		UStrAssembleLib::Str_Final_SquareBracket(this, FString(TEXT("]")));

		// 成员弄错了
		//SNew(SConstraintCanvas)
		//+ SConstraintCanvas::Slot()
		//.HAlign(HAlign_Left)
		//.VAlign(VAlign_Top)
		//[
		//	SNew(SImage)
		//]
		//+ SConstraintCanvas::Slot()
		//.HAlign(HAlign_Left)
		//.VAlign(VAlign_Top)
		//[
		//	SNew(SImage)
		//]
		//+ SConstraintCanvas::Slot()
		//.HAlign(HAlign_Left)
		//.VAlign(VAlign_Top)
		//[
		//	SNew(SImage)
		//];

	}
}

