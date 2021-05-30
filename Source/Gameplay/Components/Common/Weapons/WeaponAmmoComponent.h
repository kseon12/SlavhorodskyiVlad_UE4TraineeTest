// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "WeaponAmmoComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBulletsInMagazineChangedDelegate, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMagazineCountChangedDelegate, int);
/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UWeaponAmmoComponent : public UChildActorComponent
{
	GENERATED_BODY()

public:

	void SetInitialBulletsInMagazine(int Count);
	FORCEINLINE int GetCurrentBulletsInMagazine(){ return CurrentBulletsInMagazine;	};

	void SetInitialMagazineCount(int Count);

	void IncreaseMagazineCount(int Value);
	void Reload();
	bool DecreaseBulletsInMagazine();

	FOnBulletsInMagazineChangedDelegate OnBulletsInMagazineChanged;
	FOnMagazineCountChangedDelegate OnMagazineCountChanged;
private:

	int InitialBulletsInMagazine = 0;
	int CurrentBulletsInMagazine = 0;

	int InitialMagazineCount = 3;
	int CurrentMagazineCount = 0;

};
