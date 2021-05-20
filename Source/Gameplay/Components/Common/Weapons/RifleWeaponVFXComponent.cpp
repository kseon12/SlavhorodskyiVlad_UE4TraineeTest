// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleWeaponVFXComponent.h"

#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystem.h>

#include "Tools/MacroTools.h"

/* Constants */
const FName URifleWeaponVFXComponent::kSocketName_MuzzleFlash = "MuzzleFlash";

void URifleWeaponVFXComponent::SpawnBulletHitParticle(const FHitResult& Hit)
{
	const AActor* TargetActor = Hit.Actor.Get();
	if (!EnsureMsg(IsValid(TargetActor), TEXT("[RifleWeaponVFXComponent] FX: Actor in HitResult is not valid")))
	{
		return;
	}

	FRotator Rotation = FRotationMatrix::MakeFromX(Hit.Normal).Rotator();
	const FVector& HitLocation = Hit.Location;
	
	const FBulletHitFXData& TargetFXData = GetBulletHitFXDataForActor(TargetActor);
	if (!EnsureMsg(TargetFXData.BulletHitParticle, TEXT("[RifleWeaponVFXComponent] FX: Particle system is not set")))
	{
		return;
	}

	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(), 
		TargetFXData.BulletHitParticle,
		HitLocation, 
		Rotation,
		true);
}

void URifleWeaponVFXComponent::SpawnBulletHitDecal(const FHitResult& Hit)
{
	const AActor* TargetActor = Hit.Actor.Get();
	if (!EnsureMsg(IsValid(TargetActor), TEXT("[RifleWeaponVFXComponent] Decal: Actor in HitResult is not valid")))
	{
		return;
	}
	
	FRotator Rotation = FRotationMatrix::MakeFromX(Hit.Normal).Rotator();
	const FVector& HitLocation = Hit.Location;
	
	const FBulletHitFXData& TargetFXData = GetBulletHitFXDataForActor(TargetActor);
	if (!TargetFXData.bUseDecal)
	{
		/* Decal shouldn't be used for this actor */
		return;
	}

	if (!EnsureMsg(TargetFXData.BulletHitDecalMaterial, TEXT("[RifleWeaponVFXComponent] Decal: Material is not set")))
	{
		return;
	}
	
	UGameplayStatics::SpawnDecalAttached(
		TargetFXData.BulletHitDecalMaterial, 
		TargetFXData.DecalSize,
		TargetActor->GetRootComponent(),
		{},
		HitLocation,
		Rotation,
		EAttachLocation::KeepWorldPosition,
		TargetFXData.DecalLifeSpan);
}

void URifleWeaponVFXComponent::SpawnMuzzleFlashFX(const USkeletalMeshComponent* RifleMesh)
{
	if (!EnsureMsg(RifleMesh, TEXT("[RifleWeaponVFXComponent] Rifle Mesh doesn't exist")))
	{
		return;
	}

	if (!EnsureMsg(RifleMesh->DoesSocketExist(kSocketName_MuzzleFlash), TEXT("[RifleWeaponVFXComponent] Muzzle socket doesn't exist")))
	{
		return;
	}

	if (!EnsureMsg(MuzzleFlashParticle_Sparcles && MuzzleFlashParticle_Smoke, TEXT("[RifleWeaponVFXComponent] MuzzleFlash particle system doesn't exist")))
	{
		return;
	}
	
	FVector MuzzleSocketLocation = RifleMesh->GetSocketLocation(kSocketName_MuzzleFlash);
	FRotator MuzzleSocketRotation = RifleMesh->GetSocketRotation(kSocketName_MuzzleFlash);
	
	UGameplayStatics::SpawnEmitterAttached(
		MuzzleFlashParticle_Sparcles,
		GetOwner()->GetRootComponent(),
		kSocketName_MuzzleFlash,
		MuzzleSocketLocation,
		MuzzleSocketRotation,
		EAttachLocation::KeepWorldPosition);
	
	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(), 
		MuzzleFlashParticle_Smoke, 
		MuzzleSocketLocation,
		MuzzleSocketRotation,
		true);
}

const FBulletHitFXData& URifleWeaponVFXComponent::GetBulletHitFXDataForActor(const AActor* Actor)
{
	for (auto&& BulletHitFX : BulletHitData.BulletHitFXs)
	{
		if (Actor->IsA(BulletHitFX.Key))
		{
			return BulletHitFX.Value;
		}
	}
	
	/* Use default FX If certain is not set */
	return BulletHitData.DefaultBulletHitFX;
}
