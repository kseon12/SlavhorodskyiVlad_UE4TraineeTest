// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoundData.generated.h"

class USoundAttenuation;
class USoundConcurrency;

USTRUCT()
struct FSFXMultiplierRange
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
	float Min = 0.0f;

	UPROPERTY(EditAnywhere)
	float Max = 0.0f;

	float GetRand() const { return FMath::FRandRange(Min, Max); }
};

USTRUCT()
struct FSimpleSFXData
{
	GENERATED_USTRUCT_BODY()
	
	/** What sound effect should be spawned when the gun is fired */
	UPROPERTY(EditAnywhere)
	USoundBase* Sound;
	
	/** Random Range for volume */
	UPROPERTY(EditAnywhere)
	FSFXMultiplierRange VolumeRangeMultiplier;
	
	/** Random Range for pitch */
	UPROPERTY(EditAnywhere)
	FSFXMultiplierRange PitchRangeMultiplier;
	
	UPROPERTY(EditAnywhere)
	float StartTime = 0.0f;
	
	/** Defines how a sound changes volume with distance to the listener */
	UPROPERTY(EditAnywhere)
	USoundAttenuation* AttenuationSettings;
	
	/** Defines how a sound changes volume with distance to the listener */
	UPROPERTY(EditAnywhere)
	USoundConcurrency* ConcurrencySettings;

};
