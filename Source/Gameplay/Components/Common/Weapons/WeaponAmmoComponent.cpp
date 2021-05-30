// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAmmoComponent.h"

void UWeaponAmmoComponent::SetInitialBulletsInMagazine(int Count)
{
	InitialBulletsInMagazine = CurrentBulletsInMagazine = Count;
}

void UWeaponAmmoComponent::SetInitialMagazineCount(int Count)
{
	InitialMagazineCount = CurrentMagazineCount = Count;
}

void UWeaponAmmoComponent::IncreaseMagazineCount(int Value)
{
	CurrentMagazineCount += Value;
	OnMagazineCountChanged.Broadcast(CurrentMagazineCount);
}

void UWeaponAmmoComponent::Reload()
{
	if (CurrentMagazineCount <= 0)
	{
		return;
	}

	CurrentBulletsInMagazine = InitialBulletsInMagazine;
	--CurrentMagazineCount;

	OnMagazineCountChanged.Broadcast(CurrentMagazineCount);
	OnBulletsInMagazineChanged.Broadcast(CurrentBulletsInMagazine);
}

bool UWeaponAmmoComponent::DecreaseBulletsInMagazine()
{
	if (CurrentBulletsInMagazine <= 0)
	{
		return false;
	}

	--CurrentBulletsInMagazine;
	OnBulletsInMagazineChanged.Broadcast(CurrentBulletsInMagazine);
	return true;
}
