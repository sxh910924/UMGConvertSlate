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

	// 返回数组，数组内“.Alignment(FVector2D())”
	static FString Str_Alignment(FVector2D Alignment);

	// 返回数组，数组内“FVector2D()”
	static FString Str_Vector2D(FVector2D Vector2d);

	// 返回“.HAlign(HAlign_Left)”
	static FString Str_AlignmentH(float AlignmentH);

	// 返回“.VAlign(VAlign_Top)”
	static FString Str_AlignmentV(float AlignmentV);

	// 返回“.Offset(FMargin(1,1,1,0))”
	static FString Str_Offset(FMargin Offset);

	// 返回“FMargin(1,1,1,0)”
	static FString Str_Margin(FMargin Margin);

	// 返回“.ZOrder(0)”
	static FString Str_ZOrder(int32 ZOrder);

	// 返回“.AutoSize(true)”
	static FString Str_AutoSize(bool bAutoSize);

	// 返回“.Anchors(FAnchors())”
	static FString Str_AnchorsSlot(FAnchors Anchors);

	// 返回“FAnchors()”
	static FString Str_Anchors(FAnchors Anchors);

	// 是否相等
	static bool AnchorsIsEqual(const FAnchors &Anchors1, const FAnchors &Anchors2);

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
