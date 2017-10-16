// Fill out your copyright notice in the Description page of Project Settings.

#include "SeparationLib.h"

TMap<FString, UClass*> USeparationLib::SwitchMap;


void USeparationLib::GenerateSlateCode(UWidget* InWidget)
{
	GenerateToObjects();

	FString className = InWidget->GetClass()->GetName();
	UE_LOG(LogClass, Warning, TEXT("class name %s"), *className);
	if (SwitchMap.Contains(className))
	{
		UE_LOG(LogClass, Warning, TEXT("SwitchMap has key %s"),*className);
		UToSWidget* outer = nullptr;
		UToSWidget* targetToSWidget = NewObject<UToSWidget>(outer, SwitchMap[className]);
		if (targetToSWidget)
		{
			targetToSWidget->GenerateHead(InWidget);
			targetToSWidget->GenerateWidgetProperty();
			targetToSWidget->GenerateSpecialWidgetProperty();
			targetToSWidget->GenerateChildWidget();
		}
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("SwitchMap don't has key %s"), *className);
	}
}

void USeparationLib::GenerateToObjects()
{
	if (SwitchMap.Num() > 0) return;
	SwitchMap.Emplace(FString(TEXT("CanvasPanel")), UToSConstraintCanvas::StaticClass());
}
