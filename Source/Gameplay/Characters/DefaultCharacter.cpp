// Copyright Epic Games, Inc. All Rights Reserved.

#include "DefaultCharacter.h"

#include "Gameplay/Weapons/Rifles/RifleWeapon.h"
#include "Gameplay/Weapons/CharacterWeaponComponent.h"
#include "Gameplay/Components/Common/Input/CharacterInputArbiterComponent.h"
#include "Gameplay/Components/Common/ChracterHealthComponent.h"
#include "Gameplay/GameModes/DefaultGameMode.h"

#include <Kismet/GameplayStatics.h>
#include <TimerManager.h>

#include "Tools/MacroTools.h"
#include "Tools/Toolbox.h"

ADefaultCharacter::ADefaultCharacter()
	: Super::ACharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Health */
	Health = CreateDefaultSubobject<UChracterHealthComponent>(TEXT("Health"));
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
			Rename(L"");
			delete this;
		}), DelayBeforeRemovingAfterDeath, false);
}
