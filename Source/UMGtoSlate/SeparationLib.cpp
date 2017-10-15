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
		UE_LOG(LogClass, Warning, TEXT("yes"));
		
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("no"));
	}
}

void USeparationLib::GenerateToObjects()
{
	if (SwitchMap.Num() > 0) return;
	SwitchMap.Emplace(FString(TEXT("CanvasPanel")), UToSConstraintCanvas::StaticClass());
}
