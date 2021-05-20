// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Gameplay/Weapons/Data/WeaponsData.h"
#include "WeaponsDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UWeaponsDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	const FWeaponData& GetWeaponData(EWeaponType Type) const;
	
protected:
	
	/** Data about all the existing weapons in the game */
	UPROPERTY(EditDefaultsOnly)
	TMap<EWeaponType, FWeaponData> WeaponsData;
};
