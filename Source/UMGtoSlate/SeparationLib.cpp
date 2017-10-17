// Fill out your copyright notice in the Description page of Project Settings.

#include "SeparationLib.h"

#include "ToSConstraintCanvas.h"
#include "ToSImage.h"
#include "StrAssembleLib.h"

TMap<FString, UClass*> USeparationLib::SwitchMap;

int32 USeparationLib::LayerCount = -1;

void USeparationLib::GenerateSlateCode(UWidget* InWidget)
{
	USeparationLib::GenerateToObjectsMap();

	//static int32 namePlus = 0;

	FString className = InWidget->GetClass()->GetName();
	UE_LOG(LogClass, Warning, TEXT("class name %s"), *className);
	if (SwitchMap.Contains(className))
	{
		UE_LOG(LogClass, Warning, TEXT("SwitchMap has key %s"),*className);
		UToSWidget* targetToSWidget = NewObject<UToSWidget>();
		UClass* targetClass = SwitchMap[className];
		//FName objectName = FName(*FString::FromInt(++namePlus));
		targetToSWidget = NewObject<UToSWidget>(targetToSWidget, targetClass);
		if (targetToSWidget)
		{
			++LayerCount;
			targetToSWidget->TabCount = LayerCount;
			targetToSWidget->GenerateHead(InWidget);
			UStrAssembleLib::Str_Final_Head(targetToSWidget);

			targetToSWidget->GenerateWidgetProperty();
			UStrAssembleLib::Str_Final_Widget(targetToSWidget);

			targetToSWidget->GenerateSpecialWidgetProperty();
			UStrAssembleLib::Str_Final_SpecialWidget(targetToSWidget);

			targetToSWidget->GenerateChildWidget();
		 	UStrAssembleLib::AddUToSWidget(targetToSWidget);

			--LayerCount;
			if (LayerCount==0)
			{
				// 全部转换完毕，进入文本转换
				UStrAssembleLib::Str_FinalSlateCode();
			}
		}
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("SwitchMap don't has key %s"), *className);
	}
}

void USeparationLib::GenerateToObjectsMap()
{
	if (SwitchMap.Num() > 0) return;
	SwitchMap.Emplace(FString(TEXT("CanvasPanel")), UToSConstraintCanvas::StaticClass());
	SwitchMap.Emplace(FString(TEXT("Image")), UToSImage::StaticClass());
}
