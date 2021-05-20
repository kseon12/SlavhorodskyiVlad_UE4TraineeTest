// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

USTRUCT()
struct FSpawnTimeRange
{
	GENERATED_USTRUCT_BODY()
		
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float From = 0.0f;
		
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float To = 0.0f;

	float GetValue() const;

	bool IsValid() const { return From <= To; }
};

UCLASS()
class CASTLEDEFENDER_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASpawnPoint();

	virtual void Tick(float DeltaTime) override;

protected:
	
	virtual void BeginPlay() override;
	
	virtual void ProcessSpawn();
	
	/** What to spawn */
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SpawnObject;
	
	/** How many spawns should be during the gameplay */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "1"))
	int32 SpawnNumberOfTimes = 1;
	
	/** How ofter spawn happens (in seconds) */
	UPROPERTY(EditAnywhere)
	FSpawnTimeRange SpawnPeriod;
	
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	FSpawnTimeRange DelayBeforeFirstSpawn;

private:

	float SpawnTimer = 0.0f;
};
