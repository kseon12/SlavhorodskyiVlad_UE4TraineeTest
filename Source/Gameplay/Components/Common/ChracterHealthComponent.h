// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChracterHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeadDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedDelegate, float);

class UDamageDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEDEFENDER_API UChracterHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	float GetCurrentHealthValue() const { return CurrentHealth; }

	virtual void OnDamageReceived(float Damage, const FName& HitInBone);

	virtual void OnHealthPickUpReceived(float Value);

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return CurrentHealth <= 0.0f; }

	UFUNCTION(BlueprintCallable)
	bool IsFull() const;

	UPROPERTY(BlueprintAssignable)
	FOnDeadDelegate OnDeadDelegate;

	FOnHealthChangedDelegate OnHealthChanged;

protected:

	virtual void BeginPlay() override;

	virtual void OnDead();

	UPROPERTY(EditAnywhere)
	float InitialHealth = 100.0f;

private:

	float CurrentHealth = 0.0f;

	UPROPERTY(EditAnywhere)
	UDamageDataAsset* DamageDatabase;
};
