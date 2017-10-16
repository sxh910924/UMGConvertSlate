// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMGtoSlate.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StrAssembleLib.generated.h"

/**
 * 
 */
UCLASS()
class UMGTOSLATE_API UStrAssembleLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	// ·µ»Ø¡°SNew(ClassName)¡±
	static FString Str_SNew(const FString &ClassName);
	
	// ·µ»Ø¡°.Visibility(EVisibility::Visible)¡±
	static FString Str_Visibility(ESlateVisibility SlateVisibility);
	
};
