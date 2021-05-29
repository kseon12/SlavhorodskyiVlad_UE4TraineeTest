// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Gameplay/Items/Data/ItemsData.h"
#include "DefaultColectableItemsDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UDefaultColectableItemsDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:

	const FItemData& GetItemData(EItemType Type) const;

protected:

	/** Data about all the existing items in the game */
	UPROPERTY(EditDefaultsOnly)
		TMap<EItemType, FItemData> ItemsData;
};
