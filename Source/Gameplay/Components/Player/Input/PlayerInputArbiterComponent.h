// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Components/Common/Input/CharacterInputArbiterComponent.h"
#include "PlayerInputArbiterComponent.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UPlayerInputArbiterComponent : public UCharacterInputArbiterComponent
{
	GENERATED_BODY()
	
public:
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	virtual void StartAim() override;
	virtual void StopAim() override;
};
