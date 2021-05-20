// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/DefaultUserWidget.h"
#include "InGameWidget.generated.h"

class UInGameHUDWidget;
class UGameOverWidget;

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UInGameWidget : public UDefaultUserWidget
{
	GENERATED_BODY()

public:

	UInGameHUDWidget* GetInGameHUDWidget() const { return InGameHUD; }
	UGameOverWidget* GetGameOverWidget() const { return GameOverWidget; }
	
private:

	UPROPERTY(meta = (BindWidget))
	UInGameHUDWidget* InGameHUD;
	
	UPROPERTY(meta = (BindWidget))
	UGameOverWidget* GameOverWidget;
};
