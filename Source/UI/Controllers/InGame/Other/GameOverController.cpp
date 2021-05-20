// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverController.h"

#include "UI/Widgets/InGame/Other/GameOverWidget.h"
#include "Gameplay/GameModes/CastleDefenderGameMode.h"
#include "Controllers/DefaultPlayerController.h"
#include "Subsystems/Persistent/LevelsSubsystem.h"

#include <Kismet/GameplayStatics.h>

#include "Tools/MacroTools.h"
#include "Tools/Toolbox.h"

void UGameOverController::Initialize(UDefaultUserWidget* _Widget)
{
	Super::Initialize(_Widget);
	
	if (auto CastedWidget = Cast<UGameOverWidget>(Widget))
	{
		CastedWidget->OnBackButtonPressed.AddUObject(this, &UGameOverController::OnBackToMenuPressed);
	}

	if (auto CurrentGameMode = Cast<ACastleDefenderGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		CurrentGameMode->OnGameOverDelegate.AddUObject(this, &UGameOverController::OnGameOver);
	}
}

void UGameOverController::OnGameOver(EDefenceGameModeResult Result)
{
	ADefaultPlayerController* CurrentController = UToolbox::GetCurrentPlayerController(this);
	if (!EnsureMsg(CurrentController, TEXT("[GameOverController] CurrentController is missing")))
	{
		return;
	}

	CurrentController->SetInputMode(FInputModeUIOnly());
	CurrentController->bShowMouseCursor = true;

	if (auto CastedWidget = Cast<UGameOverWidget>(Widget))
	{
		CastedWidget->SetVisibility(ESlateVisibility::Visible);
		CastedWidget->SetVictoryResult(Result);
	}
}

void UGameOverController::OnBackToMenuPressed()
{
	if (auto LevelsSubsystem = ULevelsSubsystem::Get(this))
	{
		LevelsSubsystem->LoadLevel(EAvailableLevels::MainMenu_ElvenRuins);
	}
}
