// Fill out your copyright notice in the Description page of Project Settings.


#include "Consumable.h"
#include "Tools/Toolbox.h"


void AConsumable::BeginPlay()
{
    Super::BeginPlay();

   OnActorBeginOverlap.AddDynamic(this, &AConsumable::OnOverlapBegin);
}

float AConsumable::GetAdditiveValue()
{
    return AdditiveValue;
}

float AConsumable::GetMultiplicativeValue()
{
    return MultiplicativeValue;
}

void AConsumable::SetAdditiveValue(float Value)
{
    AdditiveValue = Value;
}

void AConsumable::SetMultiplicativeValue(float Value)
{
    MultiplicativeValue = Value;
}

void AConsumable::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{

}
