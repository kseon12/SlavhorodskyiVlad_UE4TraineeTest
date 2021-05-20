// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Other/SpawnPoint.h"
#include "AISpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API AAISpawnPoint : public ASpawnPoint
{
	GENERATED_BODY()

protected:
	
	virtual void ProcessSpawn();
};
