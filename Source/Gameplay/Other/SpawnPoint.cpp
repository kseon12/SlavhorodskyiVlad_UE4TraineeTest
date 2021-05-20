// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"

#include "Tools/MacroTools.h"

float FSpawnTimeRange::GetValue() const
{
	if (!EnsureMsg(IsValid(), TEXT("[SpawnPeriodScatter] Wrong range. Please make sure From <= To")))
	{
		return From;
	}

	return FMath::FRandRange(From, To); 
}

ASpawnPoint::ASpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	EnsureMsg(SpawnObject, TEXT("[SpawnPoint] SpawnObject is not set, nothing to spawn"));

	SpawnTimer = DelayBeforeFirstSpawn.GetValue();
}

void ASpawnPoint::ProcessSpawn()
{
	if (!SpawnObject)
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		World->SpawnActor<AActor>(SpawnObject, GetActorLocation(), GetActorRotation());
	}
}

void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpawnNumberOfTimes > 0)
	{
		if (SpawnTimer <= 0.0f)
		{
			ProcessSpawn();
			SpawnNumberOfTimes--;
			SpawnTimer = SpawnPeriod.GetValue();
		}

		SpawnTimer -= DeltaTime;
	}
}

