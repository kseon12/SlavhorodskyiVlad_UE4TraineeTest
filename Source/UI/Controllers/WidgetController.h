// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetController.generated.h"

class UDefaultUserWidget;

/**
 * Widget's purpose is to display interface, WidgetController's purpose is to control what Widget must display and react on Widget's events
 */
UCLASS(Blueprintable, BlueprintType)
class CASTLEDEFENDER_API UWidgetController : public UObject
{
	GENERATED_BODY()

public:

	virtual void Initialize(UDefaultUserWidget* _Widget);
	virtual void BeginDestroy() override;

	/** Make sure you called SetTickEnabled before overriding this method */
	virtual bool TickController(float DeltaTime) { return true; }
	
protected:

	/** Enables TickController */
	void SetTickEnabled(bool IsEnabled);

	UPROPERTY()
	UDefaultUserWidget* Widget;

private:
	
	FDelegateHandle TickHandle;
};
