// Fill out your copyright notice in the Description page of Project Settings.

#include "StrAssembleLib.h"
#include "UMGConvSlateLib.h"
#include "ToSWidget.h"

TArray<UToSWidget*> UStrAssembleLib::ToWidgets;
FString UStrAssembleLib::FinalSlateCode = FString();

FString UStrAssembleLib::Str_SNew(const FString &ClassName)
{
	return FString::Printf(TEXT("SNew(%s)"), *ClassName);
}

FString UStrAssembleLib::Str_Visibility(ESlateVisibility SlateVisibility)
{
	FString ret;
	switch (SlateVisibility)
	{
	case ESlateVisibility::Visible:
		ret = FString(TEXT(".Visibility(EVisibility::Visible)"));
		break;
	case ESlateVisibility::Collapsed:
		ret = FString(TEXT(".Visibility(EVisibility::Collapsed)"));
		break;
	case ESlateVisibility::Hidden:
		ret = FString(TEXT(".Visibility(EVisibility::Hidden)"));
		break;
	case ESlateVisibility::HitTestInvisible:
		ret = FString(TEXT(".Visibility(EVisibility::HitTestInvisible)"));
		break;
	case ESlateVisibility::SelfHitTestInvisible:
		ret = FString(TEXT(".Visibility(EVisibility::SelfHitTestInvisible)"));
		break;
	}
	return ret;
}

TArray<FString> UStrAssembleLib::Str_Alignment(FVector2D Alignment)
{
	TArray<FString> ret;
	ret.Add(UStrAssembleLib::Str_AlignmentH(Alignment.X));
	ret.Add(UStrAssembleLib::Str_AlignmentV(Alignment.Y));
	return ret;
}

FString UStrAssembleLib::Str_AlignmentH(float AlignmentH)
{
	FString ret;
	if (AlignmentH == 0.0f)
	{
		ret = FString(TEXT(".HAlign(HAlign_Left)"));
	}
	else if(AlignmentH == 0.5f)
	{
		ret = FString(TEXT(".HAlign(HAlign_Center)"));
	}
	else
	{
		ret = FString(TEXT(".HAlign(HAlign_Right)"));
	}
	return ret;
}

FString UStrAssembleLib::Str_AlignmentV(float AlignmentV)
{
	FString ret;
	if (AlignmentV == 0.0f)
	{
		ret = FString(TEXT(".VAlign(VAlign_Top)"));
	}
	else if (AlignmentV == 0.5f)
	{
		ret = FString(TEXT(".VAlign(VAlign_Center)"));
	}
	else
	{
		ret = FString(TEXT(".VAlign(VAlign_Bottom)"));
	}
	return ret;
}

FString UStrAssembleLib::Str_NormalSlotHead(const FString &ClassName)
{
	return FString::Printf(TEXT("+ %s::Slot()"),*ClassName);
}

void UStrAssembleLib::AddUToSWidget(UToSWidget* ToWidget)
{
	if (ToWidget)
	{
		ToWidgets.Add(ToWidget);
	}
}

FString UStrAssembleLib::Str_Tab(const int32 TabCount)
{
	FString ret;
	int32 count = 0;
	while (count < TabCount)
	{
		ret += FString(TEXT("\t"));
		++count;
	}
	return ret;
}

FString UStrAssembleLib::Str_NewLine()
{
	return FString(TEXT("\n"));
}

void UStrAssembleLib::Str_FinalSlateCode()
{
	UUMGConvSlateLib::CopyTextFunc(FinalSlateCode);
}

void UStrAssembleLib::Str_Final_Head(UToSWidget* ToWidget)
{
	if (ToWidget)
	{
		FString tab = UStrAssembleLib::Str_Tab(ToWidget->TabCount);
		FinalSlateCode += tab + ToWidget->HeadString + UStrAssembleLib::Str_NewLine();
	}
}

void UStrAssembleLib::Str_Final_Widget(UToSWidget* ToWidget)
{
	if (ToWidget)
	{
		// 拼通用属性
		for (FString wp : ToWidget->WidgetProperty)
		{
			FString tab = UStrAssembleLib::Str_Tab(ToWidget->TabCount);
			FinalSlateCode += tab + wp + UStrAssembleLib::Str_NewLine();
		}
	}
}

void UStrAssembleLib::Str_Final_SpecialWidget(UToSWidget* ToWidget)
{
	if (ToWidget)
	{
		// 拼特殊属性
		for (FString wsp : ToWidget->WidgetSpecialProperty)
		{
			FString tab = UStrAssembleLib::Str_Tab(ToWidget->TabCount);
			FinalSlateCode += tab + wsp + UStrAssembleLib::Str_NewLine();
		}
	}
}

void UStrAssembleLib::Str_Final_Slot(UToSWidget* ToWidget, TArray<FString> &SlotPropertyArr)
{
	if (ToWidget)
	{
		for (FString sp : SlotPropertyArr)
		{
			FString tab = UStrAssembleLib::Str_Tab(ToWidget->TabCount);
			FinalSlateCode += tab + sp + UStrAssembleLib::Str_NewLine();
		}
	}
}

void UStrAssembleLib::Str_Final_SquareBracket(UToSWidget* ToWidget, FString SquareBracketValue)
{
	if ( SquareBracketValue.Equals(TEXT("[")) || SquareBracketValue.Equals(TEXT("]")) )
	{
		if (ToWidget)
		{
			FString tab = UStrAssembleLib::Str_Tab(ToWidget->TabCount);
			FinalSlateCode += tab + SquareBracketValue + UStrAssembleLib::Str_NewLine();
		}
	}
}
