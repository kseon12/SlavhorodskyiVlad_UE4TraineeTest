// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Subsystems/SubsystemGetter.h"
#include "DataHolders/Gameplay/Items/DefaultColectableItemsDataAsset.h"
#include "ItemsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UItemsSubsystem 
	: public UGameInstanceSubsystem
	, public TSubsystemGetter<UItemsSubsystem>

{
	GENERATED_BODY()
public:

	const FItemData& GetItemData(EItemType Type) const;

private:

	
};
