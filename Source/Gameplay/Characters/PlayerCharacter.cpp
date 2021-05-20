// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Gameplay/Components/Player/PlayerCameraComponent.h"
#include "Gameplay/Components/Player/PlayerWeaponComponent.h"
#include "Gameplay/Components/Player/Input/PlayerInputArbiterComponent.h"

#include "Subsystems/Persistent/Gameplay/WeaponsSubsystem.h"

#include <GameFramework/SpringArmComponent.h>

#include "Tools/MacroTools.h"
#include "Tools/Toolbox.h"

APlayerCharacter::APlayerCharacter()
	: Super::ADefaultCharacter()
{
	/* Player's weapon logic */
	CurrentWeapon = CreateOptionalDefaultSubobject<UPlayerWeaponComponent>("CurrentWeapon");
	FName AttachmentSocket = UWeaponsSubsystem::GetDefaultAttachmentSocket();
	if (EnsureMsg(!AttachmentSocket.IsNone(), TEXT("[DefaultCharacter] Cannot attach weapon to None socket")))
	{
		CurrentWeapon->SetupAttachment(GetMesh(), AttachmentSocket);
	}
	
	/* Input Logic */
	InputArbiter = CreateDefaultSubobject<UPlayerInputArbiterComponent>(TEXT("InputArbiter"));

	/* Create a camera boom (pulls in towards the player if there is a collision) */
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	/* Create a follow camera */
	FollowCamera = CreateDefaultSubobject<UPlayerCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

FRotator APlayerCharacter::GetCameraRotation() const
{
	return UToolbox::GetPlayerCameraRotation(this);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	auto PlayerInputArbiter = Cast<UPlayerInputArbiterComponent>(InputArbiter);
	if (!EnsureMsg(PlayerInputArbiter, TEXT("[PlayerCharacter] No PlayerInputArbiter, please initialize it in the constructor")))
	{
		return;
	}

	PlayerInputArbiter->SetupPlayerInputComponent(PlayerInputComponent);
}
