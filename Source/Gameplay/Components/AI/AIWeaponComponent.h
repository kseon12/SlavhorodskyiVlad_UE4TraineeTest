// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Weapons/CharacterWeaponComponent.h"
#include "AIWeaponComponent.generated.h"

class ADefaultCharacter;

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UAIWeaponComponent : public UCharacterWeaponComponent
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	virtual void Fire(const ADefaultCharacter* Caller) override;
};
