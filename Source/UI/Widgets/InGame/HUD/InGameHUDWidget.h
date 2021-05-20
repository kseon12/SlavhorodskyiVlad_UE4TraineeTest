// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/DefaultUserWidget.h"
#include "InGameHUDWidget.generated.h"

class UTextBlock;

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
	
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DefenceTimer;

	/* Info Holder */

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MissionInfo;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentWeapon;

	bool IsNumberUpTo10(int32 Number) const;
};
