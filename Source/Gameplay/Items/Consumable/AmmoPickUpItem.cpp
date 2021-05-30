// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickUpItem.h"
#include "Gameplay/Components/Common/Weapons/WeaponAmmoComponent.h"
#include "Gameplay/Weapons/CharacterWeaponComponent.h"
#include "Gameplay/Characters/PlayerCharacter.h"
#include "Tools/MacroTools.h"

void AAmmoPickUpItem::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    auto CurrentActor = Cast<APlayerCharacter>(OtherActor);

    if (CurrentActor)
    {

		auto WeaponComponent = Cast<UCharacterWeaponComponent>(CurrentActor->GetComponentByClass(UCharacterWeaponComponent::StaticClass()));
		if (!EnsureMsg(WeaponComponent, TEXT("[AmmoPickUpItem] Cannot find WeaponComponent")))
		{
			return;
		}

		auto Weapon = Cast<AWeapon>(WeaponComponent->GetChildActor());
		if (!EnsureMsg(Weapon, TEXT("[AmmoPickUpItem] Cannot find Weapon")))
		{
			return;
		}

		auto WeaponAmmoComponent = Cast<UWeaponAmmoComponent>(Weapon->GetComponentByClass(UWeaponAmmoComponent::StaticClass()));
		if (!EnsureMsg(WeaponAmmoComponent, TEXT("[AmmoPickUpItem] Cannot find WeaponAmmoComponent")))
		{
			return;
		}

		WeaponAmmoComponent->IncreaseMagazineCount(AdditiveValue);
		Destroy();
    }
}
