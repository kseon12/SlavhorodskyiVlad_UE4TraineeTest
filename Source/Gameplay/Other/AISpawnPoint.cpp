// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawnPoint.h"

void AAISpawnPoint::ProcessSpawn()
{
	if (!GetWorld() || !SpawnObject)
	{
		return;
	}

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.Owner = this;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	auto NewPawn = GetWorld()->SpawnActor<APawn>(SpawnObject, GetActorLocation(), GetActorRotation(), ActorSpawnParams);
	if (NewPawn)
	{
		if (NewPawn->Controller == NULL)
		{
			NewPawn->SpawnDefaultController();
		}
	}
}
