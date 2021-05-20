// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"

#include "Subsystems/Persistent/Gameplay/WeaponsSubsystem.h"

#include "Gameplay/Components/AI/AIWeaponComponent.h"
#include "Gameplay/Components/Common/Input/CharacterInputArbiterComponent.h"
#include "Gameplay/Components/AI/EnemyAnalyzerComponent.h"

#include "Tools/MacroTools.h"

#include "AIController.h"

AAICharacter::AAICharacter()
	: Super::ADefaultCharacter()
{
	/* AI's weapon logic */
	CurrentWeapon = CreateOptionalDefaultSubobject<UAIWeaponComponent>("CurrentWeapon");
	FName AttachmentSocket = UWeaponsSubsystem::GetDefaultAttachmentSocket();
	if (EnsureMsg(!AttachmentSocket.IsNone(), TEXT("[AAICharacter] Cannot attach weapon to None socket")))
	{
		CurrentWeapon->SetupAttachment(GetMesh(), AttachmentSocket);
	}
	
	/* AI Input Logic */
	InputArbiter = CreateDefaultSubobject<UCharacterInputArbiterComponent>(TEXT("InputArbiter"));
	
	/* Analyzers */
	EnemyAnalyzer = CreateDefaultSubobject<UEnemyAnalyzerComponent>(TEXT("EnemyAnalyzer"));
}

void AAICharacter::OnDead()
{
	Super::OnDead();

	EnemyAnalyzer->Deactivate();

	auto AIAController = Cast<AAIController>(GetController());
	if (!EnsureMsg(AIAController, TEXT("[AAICharacter] Character has no AI controller, logic is broken")))
	{
		return;
	}

	AIAController->UnPossess();
	SetActorEnableCollision(false);
}
