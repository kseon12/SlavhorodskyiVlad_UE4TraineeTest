// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Weapons/CharacterWeaponComponent.h"
#include "PlayerWeaponComponent.generated.h"

class ADefaultCharacter;

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UPlayerWeaponComponent : public UCharacterWeaponComponent
{
	GENERATED_BODY()
	
public:

	virtual void Fire(const ADefaultCharacter* Caller) override;
};
