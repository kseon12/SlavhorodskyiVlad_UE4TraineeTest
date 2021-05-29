// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpPickUpItem.h"
#include "Gameplay/Characters/PlayerCharacter.h"
#include "Gameplay/Weapons/CharacterWeaponComponent.h"

void APowerUpPickUpItem::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    auto CurrentActor = Cast<APlayerCharacter>(OtherActor);
    if (CurrentActor)
    {
        auto WeaponComponent = Cast<UCharacterWeaponComponent>(CurrentActor->GetComponentByClass(UCharacterWeaponComponent::StaticClass()));

        if (WeaponComponent->GetIsPowerUpActive())
        {
            return;
        }
        
        WeaponComponent->SetDamageMultiplier(MultiplicativeValue);
    }

    Destroy();
}
