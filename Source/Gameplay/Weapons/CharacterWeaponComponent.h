// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "Gameplay/Weapons/Data/WeaponsData.h"
#include "CharacterWeaponComponent.generated.h"

class ADefaultCharacter;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponChangedDelegate, EWeaponType);

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UCharacterWeaponComponent : public UChildActorComponent
{
	GENERATED_BODY()
	
public:

	virtual void SetWeaponType(EWeaponType Type);
	EWeaponType GetWeaponType() const { return WeaponType; }

	virtual void Fire(const ADefaultCharacter* Caller);

	FOnWeaponChangedDelegate OnWeaponChanged;

protected:

	virtual void ParseWeaponData(const FWeaponData& Data);

private:

	EWeaponType WeaponType = EWeaponType::None;
};
