// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageDataAsset.h"

#include "Tools/MacroTools.h"

float UDamageDataAsset::GetBoneDamageMultiplier(const FName& BoneName) const
{
	if (const FCharacterBoneData* FoundData = DamageData.BonesDamageData.Find(BoneName))
	{
		return FoundData->DamageMultiplier;
	}

	return 1.0f;
}
