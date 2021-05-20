// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeaponComponent.h"

#include "Gameplay/Weapons/Rifles/RifleWeapon.h"
#include "Gameplay/Characters/PlayerCharacter.h"
#include "Gameplay/Components/Player/PlayerCameraComponent.h"

#include "Tools/Toolbox.h"
#include "Tools/GameplayToolbox.h"

void UPlayerWeaponComponent::Fire(const ADefaultCharacter* Caller)
{
	if (auto Weapon = Cast<ARifleWeapon>(GetChildActor()))
	{
		if (APlayerCameraManager* Mgr = UToolbox::GetCurrentPlayerCameraManager(this))
		{
			FVector StartPoint = Mgr->GetCameraLocation();

			FRotator CameraRotation = Mgr->GetCameraRotation();
			UGameplayToolbox::AddSpreadToWeaponRotator(CameraRotation, Weapon->GetBulletSpread());

			FVector FireLength = CameraRotation.Vector() * Weapon->GetShootingRange();
			FVector EndPoint = StartPoint + FireLength;

			Weapon->SetFirePoints({StartPoint, EndPoint});
		}
	}

	Super::Fire(Caller);
}
