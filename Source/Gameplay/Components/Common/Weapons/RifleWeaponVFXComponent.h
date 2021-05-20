// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Components/Common/Weapons/WeaponFXComponent.h"
#include "RifleWeaponVFXComponent.generated.h"

USTRUCT()
struct FBulletHitFXData
{
	GENERATED_USTRUCT_BODY()
	
	/** What effect should be spawned when the bullet is hit an obstacle */
	UPROPERTY(EditAnywhere)
	UParticleSystem* BulletHitParticle;

	/** Should we spawn decal in the bullet hit location */
	UPROPERTY(EditAnywhere)
	bool bUseDecal = true;

	/** What decal should be spawned on an obstacle when the bullet is hit the obstacle */
	UPROPERTY(EditAnywhere)
	UMaterialInterface* BulletHitDecalMaterial;
	
	/** How big the decal should be */
	UPROPERTY(EditAnywhere)
	FVector DecalSize = FVector(15.0f, 15.0f, 15.0f);
	
	/** How many time the decal should be alive */
	UPROPERTY(EditAnywhere)
	float DecalLifeSpan = 10.0f;
};

USTRUCT()
struct FBulletHitData
{
	GENERATED_USTRUCT_BODY()
	
	/** Used if FX for certain class is not set */
	UPROPERTY(EditAnywhere)
	FBulletHitFXData DefaultBulletHitFX;
	
	/** FXs for certain classes */
	UPROPERTY(EditAnywhere)
	TMap<UClass*, FBulletHitFXData> BulletHitFXs;
};

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API URifleWeaponVFXComponent : public UWeaponFXComponent
{
	GENERATED_BODY()

public:

	virtual void SpawnBulletHitParticle(const FHitResult& Hit);
	virtual void SpawnBulletHitDecal(const FHitResult& Hit);
	
	virtual void SpawnMuzzleFlashFX(const USkeletalMeshComponent* RifleMesh);
	
protected:
	
	/** What sparcles effect should be spawned when the gun is fired */
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlashParticle_Sparcles;
	/** What smoke effect should be spawned when the gun is fired */
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlashParticle_Smoke;

	/* Bullet hit FX data */
	UPROPERTY(EditAnywhere)
	FBulletHitData BulletHitData;
	
	/** Constants */
	static const FName kSocketName_MuzzleFlash;

private:

	const FBulletHitFXData& GetBulletHitFXDataForActor(const AActor* Actor);
};
