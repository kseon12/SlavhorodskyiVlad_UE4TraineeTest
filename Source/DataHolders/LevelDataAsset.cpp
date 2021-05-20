// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDataAsset.h"

#include "Tools/MacroTools.h"

FString ULevelDataAsset::GetLevelName(EAvailableLevels Level) const
{
	if (!EnsureMsg(GameLevels.Contains(Level), 
		TEXT("[LevelData] There is no such level in database. Check it carefully, maybe it is ok for design if there is no such level in the GameState")))
	{
		return {};
	}

	return GameLevels.Find(Level)->GetAssetName();
}
