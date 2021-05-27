// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterInventoryComponent.generated.h"

enum class EWeaponType;
class ADefaultCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEDEFENDER_API UCharacterInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<EWeaponType> WeaponTypeContainer;
	int8 CurrentWeaponIndex = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	EWeaponType GetWeaponRoll(int Shift);

private:

	UPROPERTY()
	ADefaultCharacter* OwnerCharacter;
};
