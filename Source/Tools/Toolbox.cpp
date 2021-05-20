// Fill out your copyright notice in the Description page of Project Settings.


#include "Toolbox.h"

#include "Controllers/DefaultPlayerController.h"

#include "Gameplay/Characters/PlayerCharacter.h"
#include "Gameplay/GameModes/DefaultGameMode.h"

ADefaultPlayerController* UToolbox::GetCurrentPlayerController(const UObject* WorldContextObject)
{
	if (UGameInstance* GInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		return Cast<ADefaultPlayerController>(GInstance->GetFirstLocalPlayerController());
	}

	return nullptr;
}

APlayerCharacter* UToolbox::GetCurrentPlayerCharacter(const UObject* WorldContextObject)
{
	if (ADefaultPlayerController* PlayerController = GetCurrentPlayerController(WorldContextObject))
	{
		return PlayerController->GetPawn<APlayerCharacter>();
	}

	return nullptr;
}

APlayerCameraManager* UToolbox::GetCurrentPlayerCameraManager(const UObject* WorldContextObject)
{
	if (ADefaultPlayerController* PlayerController = GetCurrentPlayerController(WorldContextObject))
	{
		return PlayerController->PlayerCameraManager;
	}

	return nullptr;
}

FRotator UToolbox::GetPlayerCameraRotation(const UObject* WorldContextObject)
{
	if (const APlayerCameraManager* CameraMgr = GetCurrentPlayerCameraManager(WorldContextObject))
	{
		return CameraMgr->GetCameraRotation();
	}

	return FRotator::ZeroRotator;
}

bool UToolbox::IsGameOver(const UObject* WorldContextObject)
{
	if (auto CurrentGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		return CurrentGameMode->IsGameOver();
	}

	return false;
}

bool UToolbox::IsCurrentPlayerDead(const UObject* WorldContextObject)
{
	if (const APlayerCharacter* PlayerCharacter = UToolbox::GetCurrentPlayerCharacter(WorldContextObject))
	{
		return PlayerCharacter->IsDead();
	}

	return false;
}
