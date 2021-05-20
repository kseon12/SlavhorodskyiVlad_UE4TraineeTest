// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Toolbox.generated.h"

class ADefaultPlayerController;
class APlayerCharacter;

/**
 *
 */
UCLASS()
class CASTLEDEFENDER_API UToolbox : public UObject
{
	GENERATED_BODY()

public:

	static ADefaultPlayerController* GetCurrentPlayerController(const UObject* WorldContextObject);
	
	static APlayerCharacter* GetCurrentPlayerCharacter(const UObject* WorldContextObject);
	
	static APlayerCameraManager* GetCurrentPlayerCameraManager(const UObject* WorldContextObject);

	static FRotator GetPlayerCameraRotation(const UObject* WorldContextObject);
	
	static bool IsGameOver(const UObject* WorldContextObject);
	
	static bool IsCurrentPlayerDead(const UObject* WorldContextObject);

	template<class SybsystemClass>
	static SybsystemClass* GetSubsystem(const UObject* WorldContextObject);
};

template<class SybsystemClass>
static SybsystemClass* UToolbox::GetSubsystem(const UObject* WorldContextObject)
{
	if (UGameInstance* GInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		return GInstance->GetSubsystem<SybsystemClass>();
	}

	return nullptr;
}
