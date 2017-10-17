// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMGtoSlate.h"
#include "UObject/NoExportTypes.h"
#include "ToSWidget.generated.h"

// param1 - Slot的序号
DECLARE_DELEGATE_OneParam(FSlotLoop, const int32)

/**
 * 
 */
UCLASS()
class UMGTOSLATE_API UToSWidget : public UObject
{
	GENERATED_BODY()
	
public:

	// 生成头字符串
	virtual void GenerateHead(UWidget* NewWidget);

	// 生成widget属性
	virtual void GenerateWidgetProperty();

	// 生成特殊widget属性
	virtual void GenerateSpecialWidgetProperty() { };

	// 生成下级widget
	virtual void GenerateChildWidget() {};

	// 生成Slot属性
	virtual void GenerateSlotProperty(const int32 SlotIndex) {};

protected:

	// 获得子控件个数
	int32 GetPanalWidgetChildrenCount() const;

	// 向Slot数组添加对象
	void AddSlotProperty(const int32 SlotIndex, const TArray<FString> PropertyArr);

	// 向Slot数组添加对象
	void AddSlotProperty(const int32 SlotIndex, const FString &PropertyValue);

	// 复用循环
	void LoopPanelSlot();

public:

	// 头部String，比如，SNew(SButton)
	FString HeadString = FString();

	// widget通用属性
	TArray<FString> WidgetProperty;

	// widget特殊属性
	TArray<FString> WidgetSpecialProperty;

	// 每个Slot对应的属性
	TMap<int32, TArray<FString>> SlotProperty;

	// tab个数
	int32 TabCount = 0;

protected:

	// 原UWidget
	UWidget* ThisWidget;

	// 对应的转化SWidget类名称，比如，SButton
	FString ToSWidgetClassName = FString();

	// 默认的显示设置
	ESlateVisibility ToSWidgetDefaultVisibility = ESlateVisibility::Visible;

	// 多个Slot的循环
	FSlotLoop PanelSlotLoop;

	// slot个数
	int32 ChildSlotCount = 0;


};
