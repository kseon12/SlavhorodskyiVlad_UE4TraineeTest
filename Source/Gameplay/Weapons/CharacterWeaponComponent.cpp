// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWeaponComponent.h"

#include "Subsystems/Persistent/Gameplay/WeaponsSubsystem.h"
#include "Gameplay/Components/Common/Weapons/WeaponAmmoComponent.h"
#include "Tools/MacroTools.h"

void UCharacterWeaponComponent::SetWeaponType(EWeaponType Type)
{
	if (WeaponType == Type)
	{
		return;
	}

	auto WeaponsSubsystem = UWeaponsSubsystem::Get(this);
	if (!EnsureMsg(WeaponsSubsystem, TEXT("[CharacterWeaponComponent] Weapons Subsystem is not initialized")))
	{
		return;
	}

	const FWeaponData& WeaponData = WeaponsSubsystem->GetWeaponData(Type);
	if (!EnsureMsg(WeaponData.IsValid(), TEXT("[CharacterWeaponComponent] Weapon data is not valid")))
	{
		return;
	}

	WeaponType = Type;

	ParseWeaponData(WeaponData);

	bIsPowerUpActive = false;

	OnWeaponChanged.Broadcast(WeaponType);
}

void UCharacterWeaponComponent::ParseWeaponData(const FWeaponData& Data)
{
	/* Creating weapon with specified type */
	SetChildActorClass(Data.WeaponClass);
	CreateChildActor();
	
	/* Parsing weapon data */
	SetRelativeTransform(Data.OverrideTransform);
	if (auto Weapon = Cast<AWeapon>(GetChildActor()))
	{
		Weapon->SetCooldown(Data.Cooldown);
		Weapon->SetDamage(Data.Damage);
		Weapon->SetDamageTypeClass(Data.DamageTypeClass);

		auto WeaponAmmoComponent = Cast<UWeaponAmmoComponent>(Weapon->GetComponentByClass(UWeaponAmmoComponent::StaticClass()));
		if (!EnsureMsg(WeaponAmmoComponent, TEXT("[InGameHUDController] Cannot find WeaponAmmoComponent")))
		{
			return;
		}

		WeaponAmmoComponent->SetInitialBulletsInMagazine(Data.BulletsInMagazine);
		WeaponAmmoComponent->SetInitialMagazineCount(Data.InitialMagazineCount);
	}
}

void UCharacterWeaponComponent::Fire(const ADefaultCharacter* Caller)
{
	if (auto Weapon = Cast<AWeapon>(GetChildActor()))
	{
		Weapon->Fire();
	}
}

void UCharacterWeaponComponent::SetDamageMultiplier(float Value)
{
	auto Weapon = Cast<AWeapon>(GetChildActor());

	if ( Weapon && !bIsPowerUpActive)
	{
		auto DamageValue = Weapon->GetDamage();
		Weapon->SetDamage(DamageValue * Value);
		bIsPowerUpActive = true;

		/** Subject to change on Tick check with additive time left */
		GetWorld()->GetTimerManager().SetTimer(PowerUpHandle,
			FTimerDelegate::CreateWeakLambda(this, [this,Weapon,DamageValue]
		{
			if (bIsPowerUpActive)
			{
				bIsPowerUpActive = false;
				Weapon->SetDamage(DamageValue);
			}

		}), DelayBeforeRemovingPowerUp, false);
	}
}

bool UCharacterWeaponComponent::GetIsPowerUpActive()
{
	return bIsPowerUpActive;
}

void UCharacterWeaponComponent::Reload()
{
	if (auto Weapon = Cast<AWeapon>(GetChildActor()))
	{
		Weapon->Reload();
	}
}
