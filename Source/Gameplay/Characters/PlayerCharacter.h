// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Characters/DefaultCharacter.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UPlayerCameraComponent;

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API APlayerCharacter : public ADefaultCharacter
{
	GENERATED_BODY()

public:

	APlayerCharacter();

	UFUNCTION(BlueprintCallable)
	FRotator GetCameraRotation() const;

	UPlayerCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UPlayerCameraComponent* FollowCamera;
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	/**
	* Task 1
	* Override onDead() method to avoid parent-class function call, that destroy object(in this case - player) - and cause crash
	*/
	virtual void OnDead() override
	{
	}
};
