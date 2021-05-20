// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataHolders/Sound/SoundData.h"
#include "GameplayToolbox.generated.h"

DECLARE_DELEGATE_OneParam(FCanShootDelegate, bool);

class ADefaultCharacter;

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UGameplayToolbox : public UObject
{
	GENERATED_BODY()
	
public:

	static void AddSpreadToWeaponRotator(FRotator& Rotator, float Spread);
	
	static void AsyncLineTrace(
		const UObject* WorldContextObject, 
		const FVector& StartPoint, 
		const FVector& EndPoint,
		FTraceDelegate CallbackDelegate, 
		const AActor* IgnoreActor);
	
	static void CanShootTarget(UObject* WorldContextObject, const ADefaultCharacter* Shooter, const ADefaultCharacter* Target, FCanShootDelegate ResultDelegate);
	
	static void PlaySoundAtLocation(const UObject* WorldContextObject, const FVector& Location, const FSimpleSFXData& SFXData);

};
