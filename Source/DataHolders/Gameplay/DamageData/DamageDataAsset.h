// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DamageDataAsset.generated.h"

USTRUCT()
struct FCharacterBoneData
{
	GENERATED_USTRUCT_BODY()
	
	/** How much will increase damage for this bone */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float DamageMultiplier = 1.0f;
};

USTRUCT()
struct FCharacterDamageData
{
	GENERATED_USTRUCT_BODY()
	
	/** This map describes the connection between damage and hitting into certain bone */
	UPROPERTY(EditAnywhere)
	TMap<FName, FCharacterBoneData> BonesDamageData;
};

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UDamageDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	float GetBoneDamageMultiplier(const FName& BoneName) const;
	
protected:
	
	UPROPERTY(EditAnywhere)
	FCharacterDamageData DamageData;
};
