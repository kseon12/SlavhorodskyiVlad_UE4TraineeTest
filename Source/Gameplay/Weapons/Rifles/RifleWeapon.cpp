// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleWeapon.h"

#include "Gameplay/Weapons/Data/WeaponsData.h"
#include "Gameplay/Characters/DefaultCharacter.h"
#include "Gameplay/Components/Common/Weapons/RifleWeaponVFXComponent.h"
#include "Gameplay/Components/Common/Weapons/RifleWeaponSFXComponent.h"

#include "Tools/MacroTools.h"
#include "Tools/GameplayToolbox.h"

#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/KismetMathLibrary.h>
#include <DrawDebugHelpers.h>
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystem.h>
#include <Components/SkeletalMeshComponent.h>
#include "GameFramework/Character.h"

ARifleWeapon::ARifleWeapon()
	: Super::AWeapon()
{
	WeaponVFXComp = CreateOptionalDefaultSubobject<URifleWeaponVFXComponent>("WeaponVFX");
	WeaponSFXComp = CreateOptionalDefaultSubobject<URifleWeaponSFXComponent>("WeaponSFX");
}

bool ARifleWeapon::Fire()
{
	if (!Super::Fire())
	{
		return false;
	}

	FireTraceDelegate.BindUObject(this, &ARifleWeapon::OnBulletReached);
	UGameplayToolbox::AsyncLineTrace(this, GetFirePoints().StartPoint, GetFirePoints().EndPoint, FireTraceDelegate, GetParentActor());
	
	/* Particle System */
	WeaponVFXComp->SpawnMuzzleFlashFX(Mesh);

	/* Sound */
	WeaponSFXComp->PlayFireSound();

	return true;
}

void ARifleWeapon::OnBulletReached(const FTraceHandle& Handle, FTraceDatum& Datum)
{
	auto AttackerActor = Cast<ADefaultCharacter>(GetParentActor());
	if (!EnsureMsg(AttackerActor, TEXT("[RifleWeapon] ParentActor is not a character, but it must be")))
	{
		return;
	}

	for (auto&& Hit : Datum.OutHits)
	{
		if (auto Character = Cast<ADefaultCharacter>(Hit.Actor.Get()))
		{
			/** Applying damage on the character */

			FPointDamageEvent DmgEvent;
			DmgEvent.DamageTypeClass = GetDamageTypeClass();
			DmgEvent.Damage = GetDamage();
			FVector ShotDirection = Hit.TraceEnd - Hit.TraceStart;
			ShotDirection.Normalize();
			DmgEvent.ShotDirection = ShotDirection;
			DmgEvent.HitInfo = Hit;
	
			Character->ApplyDamageMomentum(GetDamage(), DmgEvent, AttackerActor, AttackerActor);
			Character->OnDamageReceived(AttackerActor, this, Hit);
		}

		WeaponVFXComp->SpawnBulletHitParticle(Hit);
		WeaponVFXComp->SpawnBulletHitDecal(Hit);
		WeaponSFXComp->PlayBulletHitSound(Hit);
	}

#if DRAW_DEBUG_LINETRACE
	if (const UWorld* World = GetWorld())
	{
		DrawDebugLine(World, Datum.Start, Datum.End, FColor::Red, false, 5.0f);
		for (auto&& Hit : Datum.OutHits)
		{
			DrawDebugPoint(World, Hit.Location, 10.0f, FColor::Red, false, 5.0f);
		}
	}
#endif
}
