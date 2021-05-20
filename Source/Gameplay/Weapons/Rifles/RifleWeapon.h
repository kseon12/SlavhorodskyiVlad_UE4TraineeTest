// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Weapons/Weapon.h"
#include "RifleWeapon.generated.h"

class UParticleSystem;
class URifleWeaponVFXComponent;
class URifleWeaponSFXComponent;

USTRUCT()
struct FRifleWeaponData
{
	GENERATED_USTRUCT_BODY()
	
	/** How far can a bullet travel */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "100.0", ClampMax = "50000.0"))
	float ShootingRange = 5000.0f;

	/** 
	 * Bullets don't all go in a straight line, there is always an error depending on the man who shoot or the environment 
	 * 0.0 - No spread
	 * 10.0 - Max spread
	 */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float BulletSpread = 0.0f;
};

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API ARifleWeapon : public AWeapon
{
	GENERATED_BODY()

public:

	ARifleWeapon();

	virtual bool Fire() override;

	float GetShootingRange() const { return WeaponData.ShootingRange; }
	float GetBulletSpread() const { return WeaponData.BulletSpread; }

protected:
	
	/** Addition weapon design data */
	UPROPERTY(EditAnywhere)
	FRifleWeaponData WeaponData;

	/** The component is responsible for VFX made by this weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FX")
	URifleWeaponVFXComponent* WeaponVFXComp;

	/** The component is responsible for SFX made by this weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FX")
	URifleWeaponSFXComponent* WeaponSFXComp;

private:

	FTraceDelegate FireTraceDelegate;
	void OnBulletReached(const FTraceHandle& Handle, FTraceDatum& Datum);
};
