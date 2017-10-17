// Fill out your copyright notice in the Description page of Project Settings.

#include "ToSImage.h"

UToSImage::UToSImage()
{
	UToSWidget::ToSWidgetClassName = FString(TEXT("SImage"));
	UToSWidget::ToSWidgetDefaultVisibility = ESlateVisibility::Visible;
}
