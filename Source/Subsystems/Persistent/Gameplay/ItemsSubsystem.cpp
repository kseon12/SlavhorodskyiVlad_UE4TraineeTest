// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemsSubsystem.h"

#include "Gameplay/GameModes/DefaultGameMode.h"

#include "Tools/MacroTools.h"

#include <Kismet/GameplayStatics.h>

const FItemData& UItemsSubsystem::GetItemData(EItemType Type) const
{
	static FItemData NullData;

	auto CurrentGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (!EnsureMsg(CurrentGameMode, TEXT("[ItemsSubsystem] Game mode doesn't exist")))
	{
		return NullData;
	}

	const UDefaultColectableItemsDataAsset* ItemsDatabase = CurrentGameMode->GetItemsDatabase();
	if (!EnsureMsg(ItemsDatabase, TEXT("[ItemsSubsystem] LevelsDatabase doesn't exist")))
	{
		return NullData;
	}

	return ItemsDatabase->GetItemData(Type);
}
