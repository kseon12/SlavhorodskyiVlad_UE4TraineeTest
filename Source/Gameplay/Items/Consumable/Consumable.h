// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Items/Item.h"
#include "Consumable.generated.h"

/**
 * 
 */


UCLASS()
class CASTLEDEFENDER_API AConsumable : public AItem
{
	GENERATED_BODY()
	
public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float GetAdditiveValue();
	float GetMultiplicativeValue();

	void SetAdditiveValue(float Value);
	void SetMultiplicativeValue(float Value);

protected:
	UFUNCTION()
	virtual void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditDefaultsOnly)
	float AdditiveValue = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float MultiplicativeValue = 1.0f;

};
