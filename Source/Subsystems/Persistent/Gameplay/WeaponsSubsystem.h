// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Subsystems/SubsystemGetter.h"
#include "DataHolders/gameplay/Weapons/WeaponsDataAsset.h"
#include "WeaponsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UWeaponsSubsystem 
	: public UGameInstanceSubsystem
	, public TSubsystemGetter<UWeaponsSubsystem>
{
	GENERATED_BODY()
	
public:

	/** When attaching to the mesh, we have to specify a socket it should be attached to (e.g. one of the skeleton sockets) */
	static const FName& GetDefaultAttachmentSocket() { return kDefaultSocketForAttachment; }
	
	const FWeaponData& GetWeaponData(EWeaponType Type) const;

private:
	
	static const FName kDefaultSocketForAttachment;
};
