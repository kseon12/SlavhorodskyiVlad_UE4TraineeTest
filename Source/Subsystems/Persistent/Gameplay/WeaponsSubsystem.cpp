// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponsSubsystem.h"

#include "Gameplay/GameModes/DefaultGameMode.h"

#include "Tools/MacroTools.h"

#include <Kismet/GameplayStatics.h>

/* Constants */
const FName UWeaponsSubsystem::kDefaultSocketForAttachment = "hand_r";

const FWeaponData& UWeaponsSubsystem::GetWeaponData(EWeaponType Type) const
{
	static FWeaponData NullData;

	auto CurrentGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (!EnsureMsg(CurrentGameMode, TEXT("[WeaponsSubsystem] Game mode doesn't exist")))
	{
		return NullData;
	}

	const UWeaponsDataAsset* WeaponsDatabase = CurrentGameMode->GetWeaponsDatabase();
	if (!EnsureMsg(WeaponsDatabase, TEXT("[WeaponsSubsystem] LevelsDatabase doesn't exist")))
	{
		return NullData;
	}

	return WeaponsDatabase->GetWeaponData(Type);
}
