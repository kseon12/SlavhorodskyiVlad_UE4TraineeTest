// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultColectableItemsDataAsset.h"

#include "Tools/MacroTools.h"

const FItemData& UDefaultColectableItemsDataAsset::GetItemData(EItemType Type) const
{
	static FItemData NullData;

	const FItemData* FoundData = ItemsData.Find(Type);
	if (!EnsureMsg(FoundData, TEXT("[ItemsDataAsset] There is no such item in the weapons data")))
	{
		return NullData;
	}

	return *FoundData;
}
