// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCameraComponent.h"

/* Constants */
const float UPlayerCameraComponent::kAimProcessTime = 1.0f;

UPlayerCameraComponent::UPlayerCameraComponent()
	: Super::UCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	FieldOfView = DefaultFOV;
}

void UPlayerCameraComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float TargetFOV = bIsAimStarted ? AimedFOV : DefaultFOV;
	FieldOfView = FMath::Clamp(FMath::Lerp(FieldOfView, TargetFOV, DeltaTime * AimSpeed), AimedFOV, DefaultFOV);
}

void UPlayerCameraComponent::StartAiming()
{
	bIsAimStarted = true;

	PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
}

void UPlayerCameraComponent::StopAiming()
{
	bIsAimStarted = false;

	PostProcessSettings.bOverride_DepthOfFieldFocalDistance = false;
}
