// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameWidgetController.h"

#include "UI/Widgets/InGame/InGameWidget.h"
#include "UI/Widgets/InGame/HUD/InGameHUDWidget.h"
#include "UI/Widgets/InGame/Other/GameOverWidget.h"
#include "UI/Controllers/InGame/HUD/InGameHUDController.h"
#include "UI/Controllers/InGame/Other/GameOverController.h"

void UInGameWidgetController::Initialize(UDefaultUserWidget* _Widget)
{
	Super::Initialize(_Widget);
	
	if (auto CastedWidget = Cast<UInGameWidget>(_Widget))
	{
		HUDController = NewObject<UInGameHUDController>(this, HUDControllerClass);
		HUDController->Initialize(CastedWidget->GetInGameHUDWidget());
		
		GameOverController = NewObject<UGameOverController>(this, GameOverControllerClass);
		GameOverController->Initialize(CastedWidget->GetGameOverWidget());
	}
}
