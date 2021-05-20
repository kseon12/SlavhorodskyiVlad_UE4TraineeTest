// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController.h"

#include "Tools/MacroTools.h"

void UWidgetController::Initialize(UDefaultUserWidget* _Widget)
{
	EnsureMsg(_Widget, TEXT("[WidgetController (%s)] Widget is nullptr"), *GetName());
	Widget = _Widget;
}

void UWidgetController::BeginDestroy()
{
	Super::BeginDestroy();

	SetTickEnabled(false);
}

void UWidgetController::SetTickEnabled(bool IsEnabled)
{
	if (IsEnabled)
	{
		if (!EnsureMsg(!TickHandle.IsValid(), TEXT("[WidgetController] Attempt to enable tick twice. Tick is already enabled")))
		{
			return;
		}

		const auto TickDelegate = FTickerDelegate::CreateUObject(this, &UWidgetController::TickController);
		TickHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);
	}
	else
	{
		FTicker::GetCoreTicker().RemoveTicker(TickHandle);
		TickHandle.Reset();
	}
}
