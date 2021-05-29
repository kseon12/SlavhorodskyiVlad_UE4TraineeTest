// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Items/Consumable/Consumable.h"
#include "PowerUpPickUpItem.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API APowerUpPickUpItem : public AConsumable
{
	GENERATED_BODY()

protected:

	virtual void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor) override;
};
