// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGConvSlateLib.h"
#include "FileHelper.h"

void UUMGConvSlateLib::CopyTextFunc(FString InString)
{
	FFileHelper::SaveStringToFile(InString,TEXT("E:/123/aa.txt"));
}


