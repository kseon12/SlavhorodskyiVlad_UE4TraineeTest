// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUpItem.h"
#include "Gameplay/Components/Common/ChracterHealthComponent.h"
#include "Gameplay/Characters/PlayerCharacter.h"


void AHealthPickUpItem::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    auto CurrentActor = Cast<APlayerCharacter>(OtherActor);

    if (CurrentActor)
    {
        auto HealthComponent = Cast<UChracterHealthComponent>(CurrentActor->GetComponentByClass(UChracterHealthComponent::StaticClass()));

        if (HealthComponent->IsFull())
        {
            return;
        }

        HealthComponent->OnHealthPickUpReceived(AdditiveValue);
    }

    Destroy();
}
