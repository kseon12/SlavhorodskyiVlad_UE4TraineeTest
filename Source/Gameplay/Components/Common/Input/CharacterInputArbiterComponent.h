// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterInputArbiterComponent.generated.h"

class ADefaultCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEDEFENDER_API UCharacterInputArbiterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UCharacterInputArbiterComponent();
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	bool IsFiring() const { return bIsFiring; }
	UFUNCTION(BlueprintCallable)
	bool IsCrouching() const { return bIsCrouching; }
	UFUNCTION(BlueprintCallable)
	bool IsJumping() const { return bIsJumping; }
	UFUNCTION(BlueprintCallable)
	bool IsAiming() const { return bIsAiming; }

	UFUNCTION(BlueprintCallable)
	void ClearIsJumpPressed() { bIsJumping = false; }

protected:
	
	UFUNCTION(BlueprintCallable)
	virtual void StartFire();
	UFUNCTION(BlueprintCallable)
	virtual void StopFire();
	
	virtual void StartCrouch();
	virtual void StopCrouch();

	virtual void StartJump();
	virtual void StopJump();
	
	UFUNCTION(BlueprintCallable)
	virtual void StartAim();
	UFUNCTION(BlueprintCallable)
	virtual void StopAim();
	
	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);
	
	virtual void Turn(float Value);
	virtual void LookUp(float Value);

private:
	
	bool bIsFiring = false;
	bool bIsCrouching = false;
	bool bIsJumping = false;
	bool bIsAiming = false;

	UPROPERTY()
	ADefaultCharacter* OwnerCharacter;
};
