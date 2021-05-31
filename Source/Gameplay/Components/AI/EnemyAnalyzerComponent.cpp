// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnalyzerComponent.h"

#include "Gameplay/Characters/AI/AICharacter.h"
#include "Gameplay/Characters/DefaultCharacter.h"

#include "Tools/GameplayToolbox.h"
#include "Tools/MacroTools.h"

UEnemyAnalyzerComponent::UEnemyAnalyzerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UEnemyAnalyzerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEnemyAnalyzerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CheckTimer <= 0.0f)
	{
		CheckCanShootCurrentTarget();
		CheckTimer = CheckOnCanShootEvery;
	}

	CheckTimer -= DeltaTime;
}

void UEnemyAnalyzerComponent::CheckCanShootCurrentTarget()
{
	auto OwnerActor = Cast<AAICharacter>(GetOwner());
	if (!EnsureMsg(OwnerActor, TEXT("[EnemyAnalyzer] OwnerActor is nullptr")))
	{
		return;
	}

	auto CurrentTarget = Cast<ADefaultCharacter>(OwnerActor->GetCurrentTarget());
	if (!CurrentTarget)
	{
		return;
	}

	UGameplayToolbox::CanShootTarget(this, OwnerActor, CurrentTarget, FCanShootDelegate::CreateWeakLambda(this,
		[this](bool CanShoot)
		{
			bCanShootTarget = CanShoot;
		}));
}

