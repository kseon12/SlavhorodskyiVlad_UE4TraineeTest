// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controllers/WidgetController.h"
#include "InGameWidgetController.generated.h"

class UInGameHUDController;
class UGameOverController;

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UInGameWidgetController : public UWidgetController
{
	GENERATED_BODY()

public:

	virtual void Initialize(UDefaultUserWidget* _Widget) override;

private:

	/* HUD Controller */

	UPROPERTY(EditDefaultsOnly, Category = "Internal Controllers")
	TSubclassOf<UInGameHUDController> HUDControllerClass;
	UPROPERTY()
	UInGameHUDController* HUDController;

	/* GameOver Controller */

	UPROPERTY(EditDefaultsOnly, Category = "Internal Controllers")
	TSubclassOf<UGameOverController> GameOverControllerClass;
	UPROPERTY()
	UGameOverController* GameOverController;
};
