// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelDataAsset.generated.h"

UENUM()
enum class EAvailableLevels : uint8
{
	None = 0,

	MainMenu_ElvenRuins,
	DefendTheCastle_ElvenRuins
};

/**
 * 
 */
UCLASS(Blueprintable)
class CASTLEDEFENDER_API ULevelDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	FString GetLevelName(EAvailableLevels Level) const;
	
protected:

	UPROPERTY(EditDefaultsOnly, meta=(AllowedClasses="World"))
	TMap<EAvailableLevels, FSoftObjectPath> GameLevels;
};
