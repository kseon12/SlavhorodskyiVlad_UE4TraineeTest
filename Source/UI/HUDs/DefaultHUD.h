// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DefaultHUD.generated.h"

class UDefaultUserWidget;
class UWidgetController;

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API ADefaultHUD : public AHUD
{
	GENERATED_BODY()

public:

	UDefaultUserWidget* GetMainWidget() const { return MainWidget; }
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDefaultUserWidget> MainWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetController> MainWidgetControllerClass;

private:
	
	UPROPERTY()
	UDefaultUserWidget* MainWidget;
	UPROPERTY()
	UWidgetController* MainController;
};
