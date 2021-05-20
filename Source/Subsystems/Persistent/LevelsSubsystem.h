// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Subsystems/SubsystemGetter.h"
#include "DataHolders/LevelDataAsset.h"
#include "LevelsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API ULevelsSubsystem 
	: public UGameInstanceSubsystem
	, public TSubsystemGetter<ULevelsSubsystem>
{
	GENERATED_BODY()
	
public:
	
	void LoadLevel(EAvailableLevels Level);
};
