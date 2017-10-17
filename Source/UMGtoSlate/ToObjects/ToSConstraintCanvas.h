// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToSWidget.h"
#include "ToSConstraintCanvas.generated.h"

/**
 * 
 */
UCLASS()
class UMGTOSLATE_API UToSConstraintCanvas : public UToSWidget
{
	GENERATED_BODY()
	
public:

	UToSConstraintCanvas();

	virtual void GenerateChildWidget() override;

	virtual void GenerateSlotProperty(const int32 SlotIndex) override;

private:

	UCanvasPanel* m_CanvasPanel;
	
};
