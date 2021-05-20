// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWeaponComponent.h"

#include "Subsystems/Persistent/Gameplay/WeaponsSubsystem.h"

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
	}
}

void UCharacterWeaponComponent::Fire(const ADefaultCharacter* Caller)
{
	if (auto Weapon = Cast<AWeapon>(GetChildActor()))
	{
		Weapon->Fire();
	}
}
