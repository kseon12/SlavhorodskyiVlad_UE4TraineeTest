// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controllers/WidgetController.h"
#include "Gameplay/Weapons/Data/WeaponsData.h"
#include "InGameHUDController.generated.h"

class UCharacterWeaponComponent;
/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UInGameHUDController : public UWidgetController
{
	GENERATED_BODY()

public:

	virtual void Initialize(UDefaultUserWidget* _Widget) override;
	virtual bool TickController(float DeltaTime) override;

private:

	void SetTimerValue(float ValueInSeconds);
	
	void UpdateMissionInfo();
	void UpdateCurrentWeaponInfo(EWeaponType Type);
	void UpdateCurrentHealth(float Value);
	void UpdateCurrentMagazine(int Value);

	void SubscribeOnWeaponChanged();
	void SubscribeOnHealthChanged();
	void SubscribeOnMagazineSizeChanged();
};
