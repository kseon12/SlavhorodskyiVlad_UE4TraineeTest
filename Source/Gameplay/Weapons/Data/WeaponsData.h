// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Weapons/Weapon.h"
#include "WeaponsData.generated.h"

#if WITH_EDITOR
#define DRAW_DEBUG_LINETRACE 0
#else
#define DRAW_DEBUG_LINETRACE 0
#endif

UENUM()
enum class EWeaponType
{
	None = 0,

	AK47
};

USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()
		
	UPROPERTY(EditAnywhere)
	FString DisplayName;

	/** Blueprint template for a weapon */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponClass;
	
	/** Intended to define and describe a particular form of damage */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> DamageTypeClass;
	
	/** Cooldown of the weapon in seconds */
	UPROPERTY(EditDefaultsOnly)
	float Cooldown = 0.0f;
	
	UPROPERTY(EditDefaultsOnly)
	float Damage = 0.0f;
	
	/** OverrideTransform says us how the weapon should be placed inside of the character mesh */
	UPROPERTY(EditDefaultsOnly)
	FTransform OverrideTransform;

	bool IsValid() const { return 
		static_cast<bool>(WeaponClass) &&
		static_cast<bool>(DamageTypeClass); }
};

