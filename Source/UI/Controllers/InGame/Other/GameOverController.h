// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controllers/WidgetController.h"
#include "DataHolders/Gameplay/GameModes/GameModesData.h"
#include "GameOverController.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UGameOverController : public UWidgetController
{
	GENERATED_BODY()

public:

	virtual void Initialize(UDefaultUserWidget* _Widget);

private:

	UFUNCTION()
	void OnGameOver(EDefenceGameModeResult Result);

	UFUNCTION()
	void OnBackToMenuPressed();
};
