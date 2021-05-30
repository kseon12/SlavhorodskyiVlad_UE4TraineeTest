// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gameplay/Weapons/Data/WeaponsData.h"
#include "DefaultCharacter.generated.h"

class UCharacterWeaponComponent;
class UCharacterInputArbiterComponent;
class UChracterHealthComponent;
class UCharacterInventoryComponent;
class AWeapon;

UCLASS(config = Game)
class ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ADefaultCharacter();

	virtual void Tick(float DeltaTime) override;

	bool IsEnemy(AActor* Actor) const;
	bool IsDead() const;

	virtual void OnDamageReceived(const ADefaultCharacter* FromCharacter, const AWeapon* WithWeapon, const FHitResult& Hit);

	float GetCharacterCurrentHealth() const;

	void SwitchWeaponWheel(int Shift);
	void Reload();

protected:

	virtual void BeginPlay() override;

	/* Firing, Weapons */

	void Fire();

	UPROPERTY(EditAnywhere, Category = "Weapons")
	EWeaponType DefaultWeaponType = EWeaponType::AK47;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UCharacterWeaponComponent* CurrentWeapon;

	/* Enemies */

	UPROPERTY(EditAnywhere, Category = "Enemies")
	TArray<UClass*> EnemiesList;

	/* Inputs */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	UCharacterInputArbiterComponent* InputArbiter;

	/* Health */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UChracterHealthComponent* Health;

	/* Health */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UCharacterInventoryComponent* Inventory;

	/* Death */

	UFUNCTION()
	virtual void OnDead();

	/* Spawn Item*/
	UFUNCTION()
	virtual void OnDeadSpawnItem();
	void SpawnHealth();
	void SpawnPowerUp();
	void SpawnAmmo();

private:

	/** Default value 10.0f. Too big to test drop mechanics with not guarantee drop */
	UPROPERTY(EditAnywhere)
	float DelayBeforeRemovingAfterDeath = 3.0f;

	FTimerHandle DeathHandle;
};
