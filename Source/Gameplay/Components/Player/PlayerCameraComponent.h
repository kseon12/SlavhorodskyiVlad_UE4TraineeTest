// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "PlayerCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API UPlayerCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
	
public:

	UPlayerCameraComponent();
	
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	void StartAiming();
	void StopAiming();

protected:

	/** How fast aiming/unaiming will happen */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "1.0", ClampMax = "100.0"))
	float AimSpeed = 1.0f;
	
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.001", ClampMax = "360.0"))
	float DefaultFOV = 90.0f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.001", ClampMax = "360.0"))
	float AimedFOV = 50.0f;

private:
	
	/* Constants */
	static const float kAimProcessTime;

	float AimProcessTimer = 0.0f;

	bool bIsAimStarted = false;
};
