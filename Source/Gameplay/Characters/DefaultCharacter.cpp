// Copyright Epic Games, Inc. All Rights Reserved.

#include "DefaultCharacter.h"

#include "Gameplay/Weapons/Rifles/RifleWeapon.h"
#include "Gameplay/Weapons/CharacterWeaponComponent.h"
#include "Gameplay/Components/Common/Input/CharacterInputArbiterComponent.h"
#include "Gameplay/Components/Common/ChracterHealthComponent.h"
#include "Gameplay/Components/Common/Weapons/CharacterInventoryComponent.h"
#include "Gameplay/Items/Consumable/Consumable.h"
#include "Gameplay/GameModes/DefaultGameMode.h"
#include "Subsystems/Persistent/Gameplay/ItemsSubsystem.h"

#include <Kismet/GameplayStatics.h>
#include <TimerManager.h>
#include "Math/UnrealMathUtility.h"

#include "Tools/MacroTools.h"
#include "Tools/Toolbox.h"

ADefaultCharacter::ADefaultCharacter()
	: Super::ACharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Health */
	Health = CreateDefaultSubobject<UChracterHealthComponent>(TEXT("Health"));

	/* Inventory */
	Inventory = CreateDefaultSubobject<UCharacterInventoryComponent>(TEXT("Inventory"));
}

void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InputArbiter && InputArbiter->IsFiring() 
		&& CanJump()
		&& !UToolbox::IsGameOver(this))
	{
		Fire();
	}
}

void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (EnsureMsg(CurrentWeapon, TEXT("[DefaultCharacter] CurrentWeapon is not set in derived class constructor")))
	{
		CurrentWeapon->SetWeaponType(DefaultWeaponType);
	}
	
	Health->OnDeadDelegate.AddDynamic(this, &ADefaultCharacter::OnDead);
}

bool ADefaultCharacter::IsEnemy(AActor* Actor) const
{
	if (!EnsureMsg(Actor, TEXT("[DefaultCharacter] Cannot check on IsEnemy, the actor is nullptr")))
	{
		return false;
	}

	for (auto EnemyClass : EnemiesList)
	{
		if (Actor->IsA(EnemyClass))
		{
			return true;
		}
	}

	return false;
}

bool ADefaultCharacter::IsDead() const
{
	return Health->IsDead();
}

void ADefaultCharacter::OnDamageReceived(const ADefaultCharacter* FromCharacter, const AWeapon* WithWeapon, const FHitResult& Hit)
{
	/* If a certain bone was hit, we take it into account */
	FName BoneHit = NAME_None;
	if (auto SkeletalMeshComp = GetMesh())
	{
		FClosestPointOnPhysicsAsset ClosestPoint;
		SkeletalMeshComp->GetClosestPointOnPhysicsAsset(Hit.Location, ClosestPoint, true);
		BoneHit = ClosestPoint.BoneName;
	}

	Health->OnDamageReceived(WithWeapon->GetDamage(), BoneHit);
}

float ADefaultCharacter::GetCharacterCurrentHealth() const
{
	return Health->GetCurrentHealthValue();
}

void ADefaultCharacter::SwitchWeaponWheel(int Shift)
{
	auto WeaponType = Inventory->GetWeaponRoll(Shift);
	CurrentWeapon->SetWeaponType(WeaponType);
}

void ADefaultCharacter::Reload()
{
	CurrentWeapon->Reload();
}

void ADefaultCharacter::Fire()
{
	if (EnsureMsg(CurrentWeapon, TEXT("[DefaultCharacter] CurrentWeapon is not set in derived class constructor")))
	{
		CurrentWeapon->Fire(this);
	}
}

void ADefaultCharacter::OnDead()
{
	DisableInput(Cast<APlayerController>(GetController()));
	CurrentWeapon->Deactivate();
	InputArbiter->Deactivate();
	
	/* If character is dead -> remove it from the world */
    GetWorld()->GetTimerManager().SetTimer(DeathHandle, 
		FTimerDelegate::CreateWeakLambda(this, [this]
		{
			OnDeadSpawnItem();

			Rename(L"");

			/**
			* if we want to remove Actor from Level - we need to use Destroy function to notify UE to take care of it. 
			* {delete this;} "delete" object regardless of existing references on it
			*/
			Destroy();
		}), DelayBeforeRemovingAfterDeath, false);
}

void ADefaultCharacter::OnDeadSpawnItem()
{
	int RandValue = FMath::RandRange(0, 100);

	/**Every 5 number guarantee power-up to spawn. 20 lucky numbers of 100 should roughly represent 20% chance  */
	if (RandValue % 5 == 0)
	{
		auto ItemsSubsystem = UItemsSubsystem::Get(this);
		FActorSpawnParameters SpawnParameters;
		FRotator SpawnRotator{ 0.0f,0.0f, 0.0f };

		if (RandValue % 2 == 0)
		{
			const FItemData& ItemData = ItemsSubsystem->GetItemData(EItemType::HealthPickUp);
			TSubclassOf<AConsumable> ActorToSpawn = ItemData.ItemClass;

			auto Item = GetWorld()->SpawnActor<AConsumable>(ActorToSpawn, GetActorLocation(), SpawnRotator, SpawnParameters);

			if (Item)
			{
				Item->SetAdditiveValue(ItemData.AdditiveValue);
			}
		}
		else
		{
			const FItemData& ItemData = ItemsSubsystem->GetItemData(EItemType::PowerUpPickUp);
			TSubclassOf<AConsumable> ActorToSpawn = ItemData.ItemClass;

			auto Item = GetWorld()->SpawnActor<AConsumable>(ActorToSpawn, GetActorLocation(), SpawnRotator, SpawnParameters);

			if (Item)
			{
				Item->SetMultiplicativeValue(ItemData.MultiplicativeValue);
			}
		}
	}
}
