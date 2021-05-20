// Copyright Epic Games, Inc. All Rights Reserved.

#include "CastleDefenderGameMode.h"

#include "Gameplay/Characters/PlayerCharacter.h"

#include "Tools/MacroTools.h"
#include "Tools/Toolbox.h"

ACastleDefenderGameMode::ACastleDefenderGameMode()
	: Super::ADefaultGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACastleDefenderGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DefenceTimer = FMath::Max(DefenceTimer - DeltaTime, 0.0f);
	if ((DefenceTimer <= 0.0f && !bIsTimeOver) 
		|| (UToolbox::IsCurrentPlayerDead(this) && !bIsGameOverCalled))
	{
		OnGameOver();
		bIsTimeOver = true;
	}
}

bool ACastleDefenderGameMode::IsGameOver() const
{
	return IsDefenceCompleted() || UToolbox::IsCurrentPlayerDead(this);
}

void ACastleDefenderGameMode::BeginPlay()
{
	Super::BeginPlay();

	EnsureMsg(DefenceTime > 0.0f, TEXT("[CastleDefenderGameMode] DefenceTime is not set"));

	DefenceTimer = DefenceTime;
}

void ACastleDefenderGameMode::OnGameOver()
{
	GameResult = UToolbox::IsCurrentPlayerDead(this) 
		? EDefenceGameModeResult::Defeat 
		: EDefenceGameModeResult::Victory;

	OnGameOverDelegate.Broadcast(GameResult);

	bIsGameOverCalled = true;
}
