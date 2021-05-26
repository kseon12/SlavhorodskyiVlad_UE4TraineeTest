// Fill out your copyright notice in the Description page of Project Settings.


#include "ChracterHealthComponent.h"

#include "DataHolders/Gameplay/DamageData/DamageDataAsset.h"

#include "Tools/MacroTools.h"

void UChracterHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = InitialHealth;
}

void UChracterHealthComponent::OnDamageReceived(float Damage, const FName& HitInBone)
{
	if (IsDead())
	{
		/* Ignore any damage if the character is already dead */
		return;
	}

	if (!EnsureMsg(DamageDatabase, TEXT("[ChracterHealthComponent] Cannot receive damage, DamageDatabase wasn't selected")))
	{
		return;
	}

	CurrentHealth -= Damage * DamageDatabase->GetBoneDamageMultiplier(HitInBone);
	OnHealthChanged.Broadcast(CurrentHealth);

	if (IsDead())
	{
		OnDead();
	}
}

void UChracterHealthComponent::OnDead()
{
	OnDeadDelegate.Broadcast();
}


