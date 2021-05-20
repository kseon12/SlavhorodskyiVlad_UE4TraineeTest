// Fill out your copyright notice in the Description page of Project Settings.


#include "AIWeaponComponent.h"

#include "Gameplay/Weapons/Rifles/RifleWeapon.h"
#include "Gameplay/Characters/AI/AICharacter.h"
#include "Gameplay/Characters/PlayerCharacter.h"

#include "Tools/GameplayToolbox.h"
#include "Tools/MacroTools.h"

void UAIWeaponComponent::Fire(const ADefaultCharacter* Caller)
{
	auto AICharacter = Cast<AAICharacter>(Caller);
	if (!EnsureMsg(AICharacter, TEXT("[AIWeaponComponent] No AICharacter")))
	{
		return;
	}

	const ADefaultCharacter* CurrentTarget = Cast<ADefaultCharacter>(AICharacter->GetCurrentTarget());
	if (!CurrentTarget)
	{
		/* CurrentTarget is not set, it's ok and means that AI didn't find it yet */
		return;
	}

	auto Weapon = Cast<ARifleWeapon>(GetChildActor());
	if (!EnsureMsg(Weapon, TEXT("[AIWeaponComponent] Weapon doesn't exist, firing is not possible")))
	{
		return;
	}
	
	FVector StartPoint = AICharacter->GetActorLocation();
	FVector TargetPoint = CurrentTarget->GetActorLocation();
	
	FVector Direction = TargetPoint - StartPoint;
	FRotator WeaponRotation = Direction.Rotation();
			
	UGameplayToolbox::AddSpreadToWeaponRotator(WeaponRotation, Weapon->GetBulletSpread());

	FVector FireLength = WeaponRotation.Vector() * Weapon->GetShootingRange();
	FVector EndPoint = StartPoint + FireLength;

	Weapon->SetFirePoints({StartPoint, EndPoint});
	Super::Fire(AICharacter);
}
