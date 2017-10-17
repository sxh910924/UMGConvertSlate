// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMGtoSlate.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Widget.h"
#include "SeparationLib.generated.h"

/**
 * 分离器
 */
UCLASS()
class UMGTOSLATE_API USeparationLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	// 生成slate代码
	UFUNCTION(BlueprintCallable, Category = "UMGConvertSlate")
	static void GenerateSlateCode(UWidget* InWidget);

	// 生成转换对象
	static void GenerateToObjectsMap();

public:

	// 用于指定转换类的Map
	static TMap<FString, UClass*> SwitchMap;

	// 层计数
	static int32 LayerCount;
	
};
