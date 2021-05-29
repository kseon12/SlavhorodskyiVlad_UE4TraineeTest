// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Items/Consumable/Consumable.h"
#include "HealthPickUpItem.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API AHealthPickUpItem : public AConsumable
{
	GENERATED_BODY()
	
protected: 
	
	virtual void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor) override;
};
