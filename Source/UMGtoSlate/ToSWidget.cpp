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
	//SNew(SConstraintCanvas).Visibility(EVisibility::Visible).EnabledState();

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
