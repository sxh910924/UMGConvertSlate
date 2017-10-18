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

FString UStrAssembleLib::Str_Alignment(FVector2D Alignment)
{
	FString v2d = UStrAssembleLib::Str_Vector2D(Alignment);
	return FString::Printf(TEXT(".Alignment(%s)"),*v2d);
}

FString UStrAssembleLib::Str_Vector2D(FVector2D Vector2d)
{
	FString ret;

	if (Vector2d.X == Vector2d.Y)
	{
		if (FMath::IsNearlyZero(Vector2d.X))
		{
			ret = FString(TEXT("FVector2D()"));
		}
		else
		{
			ret = FString::Printf(TEXT("FVector2D(%.3ff)"), Vector2d.X);
		}
	}
	else
	{
		ret = FString::Printf(TEXT("FVector2D(%.3ff,%.3ff)"), Vector2d.X, Vector2d.Y);
	}
	
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

FString UStrAssembleLib::Str_Offset(FMargin Offset)
{
	FString margin = UStrAssembleLib::Str_Margin(Offset);
	return FString::Printf(TEXT(".Offset(%s)"),*margin);
}

FString UStrAssembleLib::Str_Margin(FMargin Margin)
{
	FString ret;
	if (Margin == FMargin())
	{
		ret = FString::Printf(TEXT("FMargin()"));
	}
	else
	{
		if ((Margin.Left == Margin.Right) && (Margin.Right == Margin.Top) && (Margin.Top == Margin.Bottom))
		{
			ret = FString::Printf(TEXT("FMargin(%.3ff)"), Margin.Left);
		}
		else if ((Margin.Left == Margin.Right) && (Margin.Top == Margin.Bottom))
		{
			ret = FString::Printf(TEXT("FMargin(%.3ff,%.3ff)"), Margin.Left, Margin.Top);
		}
		else
		{
			ret = FString::Printf(TEXT("FMargin(%.3ff,%.3ff,%.3ff,%.3ff)"), Margin.Left, Margin.Top, Margin.Right, Margin.Bottom);
		}
	}
	
	return ret;
}

FString UStrAssembleLib::Str_ZOrder(int32 ZOrder)
{
	return FString::Printf(TEXT(".ZOrder(%d)"), ZOrder);
}

FString UStrAssembleLib::Str_AutoSize(bool bAutoSize)
{
	if (bAutoSize)
	{
		return FString::Printf(TEXT(".AutoSize(true)"));
	}
	else
	{
		return FString::Printf(TEXT(".AutoSize(false)"));
	}
}

FString UStrAssembleLib::Str_AnchorsSlot(FAnchors Anchors)
{
	FString anchors = UStrAssembleLib::Str_Anchors(Anchors);
	return FString::Printf(TEXT(".Anchors(%s)"), *anchors);
}

FString UStrAssembleLib::Str_Anchors(FAnchors Anchors)
{
	FString ret;
	if (UStrAssembleLib::AnchorsIsEqual(Anchors, FAnchors()))
	{
		ret = FString::Printf(TEXT("FAnchors()"));
	}
	else
	{
		if ((Anchors.Maximum.X == Anchors.Maximum.Y) && (Anchors.Maximum.Y == Anchors.Minimum.Y) && (Anchors.Minimum.Y == Anchors.Minimum.X))
		{
			ret = FString::Printf(TEXT("FAnchors(%.1ff)"), Anchors.Maximum.X);
		}
		else if ( (Anchors.Minimum.X == Anchors.Maximum.X)&& (Anchors.Minimum.Y == Anchors.Maximum.Y) )
		{
			ret = FString::Printf(TEXT("FAnchors(%.1ff,%.1ff)"), Anchors.Minimum.X, Anchors.Minimum.Y);
		}
		else
		{
			ret = FString::Printf(TEXT("FAnchors(%.1ff,%.1ff,%.1ff,%.1ff)"), Anchors.Minimum.X, Anchors.Minimum.Y, Anchors.Maximum.X, Anchors.Maximum.Y);
		}
	}
	return ret;
}

bool UStrAssembleLib::AnchorsIsEqual(const FAnchors &Anchors1, const FAnchors &Anchors2)
{
	if (Anchors1.Minimum == Anchors2.Minimum)
	{
		if (Anchors1.Maximum == Anchors2.Maximum)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
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
	FinalSlateCode.Empty();
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
