// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/DefaultUserWidget.h"
#include "InGameHUDWidget.generated.h"

class UTextBlock;
class UProgressBar;

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UInGameHUDWidget : public UDefaultUserWidget
{
	GENERATED_BODY()

public:

	void SetDefenceTimerValue(float ValueInSeconds);
	
	void SetMissionInfo(const FString& Info);
	void SetCurrentWeaponName(const FString& Name);
	void SetCurrentHealth(float Value);
	void SetCurrentMagazines(int Value);
	void SetCurrentBullets(int Value);

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DefenceTimer;

	/* Info Holder */

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MissionInfo;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentWeapon;

	/* Health Holder */

	UPROPERTY(meta = (BindWidget))
	UProgressBar* CurrentHealth;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthText;

	/* AMMO Holder */

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BulletsCount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MagazineCount;

	bool IsNumberUpTo10(int32 Number) const;
};
