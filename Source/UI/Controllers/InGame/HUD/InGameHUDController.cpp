// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUDController.h"

#include <Kismet/GameplayStatics.h>

#include "Subsystems/Persistent/Gameplay/WeaponsSubsystem.h"

#include "Gameplay/GameModes/CastleDefenderGameMode.h"
#include "Gameplay/Characters/PlayerCharacter.h"
#include "Gameplay/Weapons/CharacterWeaponComponent.h"
#include "Gameplay/Components/Common/ChracterHealthComponent.h"
#include "UI/Widgets/InGame/HUD/InGameHUDWidget.h"
#include "Gameplay/Components/Common/Weapons/WeaponAmmoComponent.h"

#include "Tools/MacroTools.h"
#include "Tools/Toolbox.h"

void UInGameHUDController::Initialize(UDefaultUserWidget* _Widget)
{
	Super::Initialize(_Widget);

	SetTickEnabled(true);

	UpdateMissionInfo();
	SubscribeOnWeaponChanged();
	SubscribeOnHealthChanged();
}

bool UInGameHUDController::TickController(float DeltaTime)
{
	if (!Super::TickController(DeltaTime))
	{
		return false;
	}
	
	if (auto CurrentGameMode = Cast<ACastleDefenderGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		SetTimerValue(CurrentGameMode->GetRemainingDefenceTime());
	}

	return true;
}

void UInGameHUDController::SetTimerValue(float ValueInSeconds)
{
	if (auto CastedWidget = Cast<UInGameHUDWidget>(Widget))
	{
		CastedWidget->SetDefenceTimerValue(ValueInSeconds);
	}
}

void UInGameHUDController::UpdateMissionInfo()
{
	auto CastedWidget = Cast<UInGameHUDWidget>(Widget);
	if (!EnsureMsg(CastedWidget, TEXT("[InGameHUDController, 1] Widget is not set")))
	{
		return;
	}

	if (auto CurrentGameMode = Cast<ACastleDefenderGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		FString MissionDescr = CurrentGameMode->GetMissionDescription();
		FString Time = FString::FromInt(static_cast<int32>(CurrentGameMode->GetDefenceTime()));
		FString TimeUnits = CurrentGameMode->GetTimeUnits();

		CastedWidget->SetMissionInfo(MissionDescr + Time + TimeUnits);
	}
}

void UInGameHUDController::UpdateCurrentWeaponInfo(EWeaponType Type)
{
	auto CastedWidget = Cast<UInGameHUDWidget>(Widget);
	if (!EnsureMsg(CastedWidget, TEXT("[InGameHUDController, 2] Widget is not set")))
	{
		return;
	}

	auto WeaponsSubsystem = UWeaponsSubsystem::Get(this);
	if (!EnsureMsg(WeaponsSubsystem, TEXT("[InGameHUDController] Cannot get WeaponsSubsystem")))
	{
		return;
	}

	const FWeaponData& WeaponData = WeaponsSubsystem->GetWeaponData(Type);
	CastedWidget->SetCurrentWeaponName(WeaponData.DisplayName);

	SubscribeOnMagazineChanged();
	CastedWidget->SetCurrentBullets(WeaponData.BulletsInMagazine);
	CastedWidget->SetCurrentMagazines(WeaponData.InitialMagazineCount);

}

void UInGameHUDController::UpdateCurrentHealth(float Value)
{
	auto CastedWidget = Cast<UInGameHUDWidget>(Widget);
	if (!EnsureMsg(CastedWidget, TEXT("[InGameHUDController, 1] Widget is not set")))
	{
		return;
	}
	
	CastedWidget->SetCurrentHealth(Value);
}

void UInGameHUDController::UpdateCurrentBullets(int CurrentBullets)
{
	auto CastedWidget = Cast<UInGameHUDWidget>(Widget);
	if (!EnsureMsg(CastedWidget, TEXT("[InGameHUDController, 1] Widget is not set")))
	{
		return;
	}

	CastedWidget->SetCurrentBullets(CurrentBullets);
}

void UInGameHUDController::UpdateCurrentMagazines(int Value)
{
	auto CastedWidget = Cast<UInGameHUDWidget>(Widget);
	if (!EnsureMsg(CastedWidget, TEXT("[InGameHUDController, 1] Widget is not set")))
	{
		return;
	}

	CastedWidget->SetCurrentMagazines(Value);
}

void UInGameHUDController::SubscribeOnWeaponChanged()
{
	const APlayerCharacter* CurrentPlayer = UToolbox::GetCurrentPlayerCharacter(this);
	if (!EnsureMsg(CurrentPlayer, TEXT("[InGameHUDController] Cannot find player's character")))
	{
		return;
	}
	
	auto WeaponComponent = Cast<UCharacterWeaponComponent>(CurrentPlayer->GetComponentByClass(UCharacterWeaponComponent::StaticClass()));
	if (!EnsureMsg(CurrentPlayer, TEXT("[InGameHUDController] Cannot find WeaponComponent")))
	{
		return;
	}

	WeaponComponent->OnWeaponChanged.AddUObject(this, &UInGameHUDController::UpdateCurrentWeaponInfo);	
}

void UInGameHUDController::SubscribeOnHealthChanged()
{
	const APlayerCharacter* CurrentPlayer = UToolbox::GetCurrentPlayerCharacter(this);
	if (!EnsureMsg(CurrentPlayer, TEXT("[InGameHUDController] Cannot find player's character")))
	{
		return;
	}

	auto HealthComponent = Cast<UChracterHealthComponent>(CurrentPlayer->GetComponentByClass(UChracterHealthComponent::StaticClass()));
	if (!EnsureMsg(CurrentPlayer, TEXT("[InGameHUDController] Cannot find HealthComponent")))
	{
		return;
	}

	HealthComponent->OnHealthChanged.AddUObject(this, &UInGameHUDController::UpdateCurrentHealth);
}

void UInGameHUDController::SubscribeOnMagazineChanged()
{
	const APlayerCharacter* CurrentPlayer = UToolbox::GetCurrentPlayerCharacter(this);
	if (!EnsureMsg(CurrentPlayer, TEXT("[InGameHUDController] Cannot find player's character")))
	{
		return;
	}

	auto WeaponComponent = Cast<UCharacterWeaponComponent>(CurrentPlayer->GetComponentByClass(UCharacterWeaponComponent::StaticClass()));
	if (!EnsureMsg(CurrentPlayer, TEXT("[InGameHUDController] Cannot find WeaponComponent")))
	{
		return;
	}

	auto Weapon = Cast<AWeapon>(WeaponComponent->GetChildActor());
	if (!EnsureMsg(Weapon, TEXT("[InGameHUDController] Cannot find Weapon")))
	{
		return;
	}

	auto WeaponAmmoComponent = Cast<UWeaponAmmoComponent>(Weapon->GetComponentByClass(UWeaponAmmoComponent::StaticClass()));
	if (!EnsureMsg(WeaponAmmoComponent, TEXT("[InGameHUDController] Cannot find WeaponAmmoComponent")))
	{
		return;
	}

	WeaponAmmoComponent->OnBulletsInMagazineChanged.AddUObject(this, &UInGameHUDController::UpdateCurrentBullets);
	WeaponAmmoComponent->OnMagazineCountChanged.AddUObject(this, &UInGameHUDController::UpdateCurrentMagazines);
}

