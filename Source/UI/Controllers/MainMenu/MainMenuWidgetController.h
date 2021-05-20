// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controllers/WidgetController.h"
#include "MainMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UMainMenuWidgetController : public UWidgetController
{
	GENERATED_BODY()

public:

	virtual void Initialize(UDefaultUserWidget* _Widget) override;

private:

	UFUNCTION()
	void OnPlayClicked();
};
