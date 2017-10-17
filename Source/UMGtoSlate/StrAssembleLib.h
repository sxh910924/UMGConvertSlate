// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMGtoSlate.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StrAssembleLib.generated.h"

class UToSWidget;

/**
 * 
 */
UCLASS()
class UMGTOSLATE_API UStrAssembleLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public: // 基础字符串

	// 返回“SNew(ClassName)”
	static FString Str_SNew(const FString &ClassName);
	
	// 返回“.Visibility(EVisibility::Visible)”
	static FString Str_Visibility(ESlateVisibility SlateVisibility);

	// 返回数组，数组内“.HAlign(HAlign_Left)”、“.VAlign(VAlign_Top)”
	static TArray<FString> Str_Alignment(FVector2D Alignment);

	// 返回“.HAlign(HAlign_Left)”
	static FString Str_AlignmentH(float AlignmentH);

	// 返回“.VAlign(VAlign_Top)”
	static FString Str_AlignmentV(float AlignmentV);

	// 返回“+ ClassName::Slot()”
	static FString Str_NormalSlotHead(const FString &ClassName);

	// 添加UToWidget，以备最终转化使用
	static void AddUToSWidget(UToSWidget* ToWidget);

	// 返回多个“\t”
	static FString Str_Tab(const int32 TabCount);

	// 返回一个“\n”
	static FString Str_NewLine();

	// 返回最后的slate代码
	static void Str_FinalSlateCode();

public:	// 行字符串

	// 拼头
	static void Str_Final_Head(UToSWidget* ToWidget);

	// 拼widget通用属性
	static void Str_Final_Widget(UToSWidget* ToWidget);

	// 拼widget特殊属性
	static void Str_Final_SpecialWidget(UToSWidget* ToWidget);

	// 拼Slot
	static void Str_Final_Slot(UToSWidget* ToWidget, TArray<FString> &SlotPropertyArr);

	// 拼[或]
	static void Str_Final_SquareBracket(UToSWidget* ToWidget, FString SquareBracketValue);



private:

	// 保存所有待转换对象
	static TArray<UToSWidget*> ToWidgets;

	// 最终的slate代码
	static FString FinalSlateCode;
	
};
