// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMGtoSlate.h"
#include "UObject/NoExportTypes.h"
#include "ToSWidget.generated.h"

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

protected:

	// 获得子控件个数
	int32 GetPanalWidgetChildrenCount() const;

protected:

	UWidget* ThisWidget;

	// 头部String，比如，SNew(SButton)
	FString HeadString = FString();

	// widget通用属性
	TArray<FString> WidgetProperty;

	// widget特殊属性
	TArray<FString> WidgetSpecialProperty;

	// 对应的转化SWidget类名称，比如，SButton
	FString ToSWidgetClassName = FString();

	// 默认的显示设置
	ESlateVisibility ToSWidgetDefaultVisibility = ESlateVisibility::Visible;

};
