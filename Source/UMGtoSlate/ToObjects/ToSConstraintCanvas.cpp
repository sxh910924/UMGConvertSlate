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

		if (cps->LayoutData.Alignment != FVector2D(0.5f,0.5f))
		{
			FString alignment = UStrAssembleLib::Str_Alignment(cps->LayoutData.Alignment);
			AddSlotProperty(SlotIndex, alignment);
		}
		
		if (cps->LayoutData.Offsets != FMargin(0, 0, 1, 1))
		{
			FString offset = UStrAssembleLib::Str_Offset(cps->LayoutData.Offsets);
			AddSlotProperty(SlotIndex, offset);
		}
		
		if (cps->ZOrder != 0)
		{
			FString zorder = UStrAssembleLib::Str_ZOrder(cps->ZOrder);
			AddSlotProperty(SlotIndex, zorder);
		}
		
		if (cps->bAutoSize != false)
		{
			FString autoSize = UStrAssembleLib::Str_AutoSize(cps->bAutoSize);
			AddSlotProperty(SlotIndex, autoSize);
		}

		if (!UStrAssembleLib::AnchorsIsEqual(cps->LayoutData.Anchors, FAnchors()))
		{
			FString anchors = UStrAssembleLib::Str_AnchorsSlot(cps->LayoutData.Anchors);
			AddSlotProperty(SlotIndex, anchors);
		}
		
		// 拼装slot到最终字符串
		TArray<FString> &slotProperty = SlotProperty[SlotIndex];
		UStrAssembleLib::Str_Final_Slot(this, slotProperty);

		// [
		UStrAssembleLib::Str_Final_SquareBracket(this, FString(TEXT("[")));

		// 处理Slot里面的对象
		UWidget* slotWidget = Cast<UWidget>(m_CanvasPanel->GetChildAt(SlotIndex));
		if (slotWidget)
		{
			USeparationLib::GenerateSlateCode(slotWidget);
		}

		// ]
		UStrAssembleLib::Str_Final_SquareBracket(this, FString(TEXT("]")));

	}
}

