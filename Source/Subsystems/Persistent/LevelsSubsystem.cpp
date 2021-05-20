// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelsSubsystem.h"

#include "Tools/MacroTools.h"

#include "Controllers/DefaultPlayerController.h"

#include "Gameplay/GameModes/DefaultGameMode.h"

#include "Kismet/GameplayStatics.h"

void ULevelsSubsystem::LoadLevel(EAvailableLevels Level)
{
	auto CurrentGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (!EnsureMsg(CurrentGameMode, TEXT("[LevelsSubsystem] Game mode doesn't exist")))
	{
		return;
	}

	const ULevelDataAsset* LevelsDatabase = CurrentGameMode->GetLevelsDatabase();
	if (!EnsureMsg(LevelsDatabase, TEXT("[LevelsSubsystem] LevelsDatabase doesn't exist")))
	{
		return;
	}

	FString LevelName = LevelsDatabase->GetLevelName(Level);
	if (!EnsureMsg(!LevelName.IsEmpty(), TEXT("[LevelsSubsystem] Unable to load missing level")))
	{
		return;
	}
	
	UGameplayStatics::OpenLevel(this, FName(LevelName));
}

