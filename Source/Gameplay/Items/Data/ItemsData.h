// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Items/Item.h"
#include "ItemsData.generated.h"


UENUM()
enum class EItemType
{
	None = 0,

	HealthPickUp,

	PowerUpPickUp
};

USTRUCT()
struct FItemData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString DisplayName;

	/** Blueprint template for a weapon */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AItem> ItemClass;

	UPROPERTY(EditDefaultsOnly)
	float AdditiveValue = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float MultiplicativeValue = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	FTransform OverrideTransform;

	bool IsValid() const { return	static_cast<bool>(ItemClass); }
};
