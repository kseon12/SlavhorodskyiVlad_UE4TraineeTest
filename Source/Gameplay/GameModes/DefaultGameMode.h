// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGameMode.generated.h"

class ULevelDataAsset;
class UWeaponsDataAsset;
class UDefaultColectableItemsDataAsset;


/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API ADefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual bool IsGameOver() const { return false; }
	
	/** Every particular game mode tells us about levels available to load */
	const ULevelDataAsset* GetLevelsDatabase() const { return LevelsDatabase; }
	
	/** Every particular game mode tells us about weapons available in the game */
	const UWeaponsDataAsset* GetWeaponsDatabase() const { return WeaponsDatabase; }

	/** Every particular game mode tells us about items available in the game */
	const UDefaultColectableItemsDataAsset* GetItemsDatabase() const	{ return ItemsDatabase; }
	
protected:

	UPROPERTY(EditDefaultsOnly)
	ULevelDataAsset* LevelsDatabase;
	
	UPROPERTY(EditDefaultsOnly)
	UWeaponsDataAsset* WeaponsDatabase;

	UPROPERTY(EditDefaultsOnly)
	UDefaultColectableItemsDataAsset* ItemsDatabase;
};
