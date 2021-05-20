// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/DefaultUserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;

DECLARE_MULTICAST_DELEGATE(FOnPlayPressedDelegate);

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UMainMenuWidget : public UDefaultUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	FOnPlayPressedDelegate OnPlayClicked;
	
protected:

	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;

private:

	UFUNCTION()
	void OnPlayButtonClicked();
};
