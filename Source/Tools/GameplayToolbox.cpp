// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayToolbox.h"

#include <Kismet/GameplayStatics.h>

#include "Gameplay/Characters/DefaultCharacter.h"

#include "Tools/MacroTools.h"

void UGameplayToolbox::AddSpreadToWeaponRotator(FRotator& Rotator, float Spread)
{
	float RandPitchStep_1 = FMath::FRandRange(-Spread, Spread);
	float RandYawStep_1 = FMath::FRandRange(-Spread, Spread);

	float RandPitchStep_2 = FMath::FRandRange(-Spread, FMath::FRandRange(RandPitchStep_1, Spread));
	float RandYawStep_2 = FMath::FRandRange(-Spread, FMath::FRandRange(RandYawStep_1, Spread));
	
	Rotator.Add(RandPitchStep_2 /*vertical*/, RandYawStep_2 /*horizontal*/, 0.0f);
}

void UGameplayToolbox::AsyncLineTrace(
	const UObject* WorldContextObject, 
	const FVector& StartPoint, 
	const FVector& EndPoint,
	FTraceDelegate CallbackDelegate, 
	const AActor* IgnoreActor)
{
	if (!EnsureMsg(WorldContextObject, TEXT("[GameplayToolbox, AsyncLineTrace] WorldContextObject is nullptr")))
	{
		return;
	}
	
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("LineTraceSingle")), false, IgnoreActor);
	WorldContextObject->GetWorld()->AsyncLineTraceByChannel(
		EAsyncTraceType::Single,
		StartPoint,
		EndPoint,
		ECollisionChannel::ECC_Pawn,
		RV_TraceParams,
		FCollisionResponseParams::DefaultResponseParam,
		&CallbackDelegate
	);
}

void UGameplayToolbox::CanShootTarget(UObject* WorldContextObject, const ADefaultCharacter* Shooter, const ADefaultCharacter* Target, FCanShootDelegate ResultDelegate)
{
	if (!EnsureMsg(WorldContextObject, TEXT("[GameplayToolbox, CanShootTarget] WorldContextObject is nullptr")))
	{
		ResultDelegate.Execute(false);
		return;
	}
	
	if (!EnsureMsg(Shooter, TEXT("[GameplayToolbox, CanShootTarget] Shooter is nullptr")))
	{
		ResultDelegate.Execute(false);
		return;
	}
	
	if (!EnsureMsg(Target, TEXT("[GameplayToolbox, CanShootTarget] Target is nullptr")))
	{
		ResultDelegate.Execute(false);
		return;
	}
	
	FVector StartPoint = Shooter->GetActorLocation();
	FVector EndPoint = Target->GetActorLocation();

	TWeakObjectPtr<const ADefaultCharacter> WeakShooter = Shooter;
	TWeakObjectPtr<const ADefaultCharacter> WeakTarget = Target;

	UGameplayToolbox::AsyncLineTrace(WorldContextObject, StartPoint, EndPoint, FTraceDelegate::CreateWeakLambda(WorldContextObject, 
		[StartPoint, EndPoint, WeakShooter, WeakTarget, ResultDelegate](const FTraceHandle& Handle, FTraceDatum& Datum)
		{
			const ADefaultCharacter* Shooter = WeakShooter.Get();
			if (!EnsureMsg(Shooter, TEXT("[GameplayToolbox, CanShootTarget] Weak Shooter is nullptr")))
			{
				ResultDelegate.Execute(false);
				return;
			}
			const ADefaultCharacter* Target = WeakTarget.Get();
			if (!EnsureMsg(Target, TEXT("[GameplayToolbox, CanShootTarget] Weak Target is nullptr")))
			{
				ResultDelegate.Execute(false);
				return;
			}

			for (auto&& Hit : Datum.OutHits)
			{
				if (Shooter->IsEnemy(Hit.Actor.Get()))
				{
					ResultDelegate.Execute(true);
					return;
				}
			}
			
			ResultDelegate.Execute(false);
		}), Shooter);
}

void UGameplayToolbox::PlaySoundAtLocation(const UObject* WorldContextObject, const FVector& Location, const FSimpleSFXData& SFXData)
{
	if (!EnsureMsg(WorldContextObject, TEXT("[GameplayToolbox, PlaySoundAtLocation] WorldContextObject is nullptr")))
	{
		return;
	}
	
	if (!EnsureMsg(SFXData.Sound, TEXT("[GameplayToolbox, PlaySoundAtLocation] Sound is not set")))
	{
		return;
	}
	
	UGameplayStatics::PlaySoundAtLocation(
		WorldContextObject,
		SFXData.Sound,
		Location,
		SFXData.VolumeRangeMultiplier.GetRand(),
		SFXData.PitchRangeMultiplier.GetRand(),
		SFXData.StartTime,
		SFXData.AttenuationSettings,
		SFXData.ConcurrencySettings);
}
