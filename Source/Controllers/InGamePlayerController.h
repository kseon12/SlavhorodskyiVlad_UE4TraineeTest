// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultPlayerController.h"
#include "InGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API AInGamePlayerController : public ADefaultPlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
};
