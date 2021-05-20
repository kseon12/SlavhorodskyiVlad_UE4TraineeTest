// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidgetController.h"

#include "UI/Widgets/MainMenu/MainMenuWidget.h"
#include "Subsystems/Persistent/LevelsSubsystem.h"

#include "Tools/MacroTools.h"

void UMainMenuWidgetController::Initialize(UDefaultUserWidget* _Widget)
{
	Super::Initialize(_Widget);

	if (auto CastedWidget = Cast<UMainMenuWidget>(_Widget))
	{
		CastedWidget->OnPlayClicked.AddUObject(this, &UMainMenuWidgetController::OnPlayClicked);
	}
	else
	{
		EnsureMsg(false, TEXT("[MainMenuWidgetController] No Widget set"));
	}
}

void UMainMenuWidgetController::OnPlayClicked()
{
	if (auto LevelsSubsystem = ULevelsSubsystem::Get(this))
	{
		LevelsSubsystem->LoadLevel(EAvailableLevels::DefendTheCastle_ElvenRuins);
	}
}
