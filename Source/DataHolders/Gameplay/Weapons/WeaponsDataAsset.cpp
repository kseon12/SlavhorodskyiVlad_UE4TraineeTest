// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponsDataAsset.h"

#include "Tools/MacroTools.h"

const FWeaponData& UWeaponsDataAsset::GetWeaponData(EWeaponType Type) const
{
	static FWeaponData NullData;

	const FWeaponData* FoundData = WeaponsData.Find(Type);
	if (!EnsureMsg(FoundData, TEXT("[WeaponsDataAsset] There is no such weapon in the weapons data")))
	{
		return NullData;
	}

	return *FoundData;
}
