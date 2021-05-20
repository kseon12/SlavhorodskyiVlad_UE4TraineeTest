// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/GameModes/DefaultGameMode.h"
#include "DataHolders/Gameplay/GameModes/GameModesData.h"
#include "CastleDefenderGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameOverDelegate, EDefenceGameModeResult);

UCLASS()
class ACastleDefenderGameMode : public ADefaultGameMode
{
	GENERATED_BODY()

public:

	ACastleDefenderGameMode();
	
	virtual void Tick(float DeltaTime) override;

	virtual bool IsGameOver() const;

	EDefenceGameModeResult GetDefenceResult() const { return GameResult; }
	bool IsDefenceCompleted() const { return bIsTimeOver; }
	float GetDefenceTime() const { return DefenceTime; }
	float GetRemainingDefenceTime() const { return DefenceTimer; }
	
	const FString& GetMissionDescription() const { return MissionDescription; }
	const FString& GetTimeUnits() const { return TimeUnits; }

	FOnGameOverDelegate OnGameOverDelegate;

protected:
	
	virtual void BeginPlay() override;
	
	virtual void OnGameOver();

private:
	
	UPROPERTY(EditAnywhere)
	FString MissionDescription;
	UPROPERTY(EditAnywhere)
	FString TimeUnits;

	/** How much time player have to defend the castle (in seconds) */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "3600.0"))
	float DefenceTime = 0.0f;

	float DefenceTimer = 0.0f;
	bool bIsTimeOver = false;
	bool bIsGameOverCalled = false;

	EDefenceGameModeResult GameResult = EDefenceGameModeResult::None;
};



