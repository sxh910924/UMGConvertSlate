// Fill out your copyright notice in the Description page of Project Settings.

#include "StrAssembleLib.h"

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
