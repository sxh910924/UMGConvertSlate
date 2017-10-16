// Fill out your copyright notice in the Description page of Project Settings.

#include "ToSConstraintCanvas.h"

UToSConstraintCanvas::UToSConstraintCanvas()
{
	UToSWidget::ToSWidgetClassName = FString(TEXT("SConstraintCanvas"));
	UToSWidget::ToSWidgetDefaultVisibility = ESlateVisibility::SelfHitTestInvisible;
}

void UToSConstraintCanvas::GenerateChildWidget()
{
	int32 slotCount = GetPanalWidgetChildrenCount();
	if (slotCount==0)
	{
		return;
	}

	UCanvasPanel* canvasPanel = Cast<UCanvasPanel>(UToSWidget::ThisWidget);
	if (!canvasPanel)
	{
		return;
	}

	for (int32 loop = 0; loop < slotCount; ++loop)
	{
		UCanvasPanelSlot* cps = Cast<UCanvasPanelSlot>(canvasPanel->GetChildAt(loop));
		//cps->LayoutData;
		//cps->bAutoSize;
		//ZOrder
	}

}
