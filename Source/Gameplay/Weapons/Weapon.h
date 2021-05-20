// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

USTRUCT()
struct FFirePoints
{
	GENERATED_USTRUCT_BODY()
	
	FVector StartPoint = FVector::ZeroVector;
	FVector EndPoint = FVector::ZeroVector;
};

UCLASS()
class CASTLEDEFENDER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AWeapon();

	virtual bool Fire();
	virtual bool CanFire() const;

	/** If this weapon has throwing type of attack, we should set start and end point of the throwed object (e.g. Bullet or Grenade) */
	virtual void SetFirePoints(const FFirePoints& _FirePoints) { FirePoints = _FirePoints; }
	const FFirePoints& GetFirePoints() const { return FirePoints; }

	virtual void Tick(float DeltaTime) override;
	
	void SetCooldown(float _Cooldown) { Cooldown = _Cooldown; }
	FORCEINLINE float GetCooldown() const { return Cooldown; }
	
	void SetDamageTypeClass(TSubclassOf<UDamageType> _DamageTypeClass) { DamageTypeClass = _DamageTypeClass; }
	TSubclassOf<UDamageType> GetDamageTypeClass() const { return DamageTypeClass; }

	void SetDamage(float _Damage) { Damage = _Damage; }
	FORCEINLINE float GetDamage() const { return Damage; }

protected:

	/** The main skeletal mesh associated with this Weapon. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Mesh;

private:
	
	TSubclassOf<UDamageType> DamageTypeClass;

	FFirePoints FirePoints;
	
	bool bIsCooledDown = false;
	float CurrentCooldown = 0.0f;
	float Cooldown = 0.0f;

	float Damage = 0.0f;
};
