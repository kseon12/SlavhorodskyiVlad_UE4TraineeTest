// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Components/Common/Weapons/WeaponFXComponent.h"
#include "DataHolders/Sound/SoundData.h"
#include "RifleWeaponSFXComponent.generated.h"

USTRUCT()
struct FRifleSFXData
{
	GENERATED_USTRUCT_BODY()
	
	/* Shot */

	UPROPERTY(EditAnywhere)
	FSimpleSFXData SingleShotSound;
	
	/* Bullet hit */

	UPROPERTY(EditAnywhere)
	FSimpleSFXData BulletHitSoundDefault;
	
	/** Bullet hit SFXs for certain classes */
	UPROPERTY(EditAnywhere)
	TMap<UClass*, FSimpleSFXData> BulletHitSounds;
};

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API URifleWeaponSFXComponent : public UWeaponFXComponent
{
	GENERATED_BODY()

public:
	
	virtual void PlayFireSound();
	virtual void PlayBulletHitSound(const FHitResult& Hit);
	
protected:

	UPROPERTY(EditAnywhere)
	FRifleSFXData SFXData;

private:

	const FSimpleSFXData& GetBulletHitSFXDataForActor(const AActor* Actor);
};
