// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterInventoryComponent.h"
#include "Gameplay/Weapons/Data/WeaponsData.h"
#include "Gameplay/Characters/DefaultCharacter.h"
#include "Tools/MacroTools.h"

// Sets default values for this component's properties
UCharacterInventoryComponent::UCharacterInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCharacterInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	OwnerCharacter = Cast<ADefaultCharacter>(GetOwner());
	EnsureMsg(OwnerCharacter, TEXT("[InputArbiter] Owner is not character which is wrong"));
	
	WeaponTypeContainer.Add(EWeaponType::AK47);
	WeaponTypeContainer.Add(EWeaponType::AK74);
	WeaponTypeContainer.Add(EWeaponType::AR4);
}


// Called every frame
void UCharacterInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EWeaponType UCharacterInventoryComponent::GetWeaponRoll(int Shift)
{
	CurrentWeaponIndex += Shift;

	if (CurrentWeaponIndex >= WeaponTypeContainer.Num())
	{
		CurrentWeaponIndex = 0;
	}
	else if (CurrentWeaponIndex < 0)
	{
		CurrentWeaponIndex = WeaponTypeContainer.Num() - 1;
	}

	return WeaponTypeContainer[CurrentWeaponIndex];
}
