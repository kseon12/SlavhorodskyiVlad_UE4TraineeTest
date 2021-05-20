// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAIController.h"

#include "Gameplay/Characters/AI/AICharacter.h"
#include "Gameplay/Characters/PlayerCharacter.h"
#include "Gameplay/Components/AI/EnemyAnalyzerComponent.h"

#include "Tools/MacroTools.h"
#include "Tools/Toolbox.h"

#include "BehaviorTree/BlackboardComponent.h"

/* Constants */
const FName ADefaultAIController::kBlackboardValue_Enemy = "Enemy";
const FName ADefaultAIController::kBlackboardValue_SelfActor = "SelfActor";
const FName ADefaultAIController::kBlackboardValue_CanShootEnemy = "CanShootEnemy";
const FName ADefaultAIController::kBlackboardValue_IsCloseToPlayer = "IsCloseToPlayer";
const FName ADefaultAIController::kBlackboardValue_IsGameOver = "IsGameOver";

ADefaultAIController::ADefaultAIController()
	: Super::AAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADefaultAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ADefaultAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EnsurePropertiesInitialized();

	UpdateCanShootTarget();
	UpdateIsCloseToPlayer();
	UpdateIsGameOver();
}

void ADefaultAIController::UpdateBoolValue(const FName& valueName, bool NewValue, bool& CurrentValue)
{
	if (!Blackboard)
	{
		return;
	}

	if (NewValue == CurrentValue)
	{
		return;
	}

	CurrentValue = NewValue;
	Blackboard->SetValueAsBool(valueName, NewValue);
}

void ADefaultAIController::UpdateCanShootTarget()
{
	if (!EnemyAnalyzer)
	{
		return;
	}

	UpdateBoolValue(kBlackboardValue_CanShootEnemy, EnemyAnalyzer->CanShootCurrentTarget(), bLastCanShootTarget);
}

void ADefaultAIController::UpdateIsCloseToPlayer()
{
	if (!AICharacter || !CurrentEnemy)
	{
		return;
	}

	float Length = (AICharacter->GetActorLocation() - CurrentEnemy->GetActorLocation()).Size();
	bool NewIsCloseToPlayer = Length < 1000.0f;

	UpdateBoolValue(kBlackboardValue_IsCloseToPlayer, NewIsCloseToPlayer, bLastIsCloseToPlayer);
}

void ADefaultAIController::UpdateIsGameOver()
{	
	UpdateBoolValue(kBlackboardValue_IsGameOver, UToolbox::IsGameOver(this), bLastIsGameOver);
}

void ADefaultAIController::EnsurePropertiesInitialized()
{
	if (Blackboard)
	{
		bIsBlackboardReady = true;
	}

	if (bIsBlackboardReady && !bIsInitialized)
	{
		OnBlackboardInitialized();
	}
}

void ADefaultAIController::OnBlackboardInitialized()
{
	if (!EnsureMsg(Blackboard, TEXT("[DefaultAIController] Blackboard is not initialized")))
	{
		return;
	}
	
	CurrentEnemy = UToolbox::GetCurrentPlayerCharacter(this);

	Blackboard->SetValueAsObject(kBlackboardValue_Enemy, CurrentEnemy);
	
	AICharacter = Cast<AAICharacter>(Blackboard->GetValueAsObject(kBlackboardValue_SelfActor));
	if (EnsureMsg(AICharacter, TEXT("[DefaultAIController] AICharacter (SelfActor) is not in Blackboard")))
	{
		EnemyAnalyzer = Cast<UEnemyAnalyzerComponent>(AICharacter->GetComponentByClass(UEnemyAnalyzerComponent::StaticClass()));
	}

	bIsInitialized = true;
}
