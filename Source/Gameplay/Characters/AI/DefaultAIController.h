// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DefaultAIController.generated.h"

class UBlackboardComponent;
class AAICharacter;
class UEnemyAnalyzerComponent;
class ADefaultCharacter;

/**
 * 
 */
UCLASS()
class CASTLEDEFENDER_API ADefaultAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	ADefaultAIController();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

protected:
	
	static const FName kBlackboardValue_Enemy;
	static const FName kBlackboardValue_SelfActor;
	static const FName kBlackboardValue_CanShootEnemy;
	static const FName kBlackboardValue_IsCloseToPlayer;
	static const FName kBlackboardValue_IsGameOver;

private:

	UPROPERTY()
	AAICharacter* AICharacter;
	
	UPROPERTY()
	UEnemyAnalyzerComponent* EnemyAnalyzer;
	
	UPROPERTY()
	ADefaultCharacter* CurrentEnemy;

	void UpdateBoolValue(const FName& valueName, bool NewValue, bool& CurrentValue);

	bool bLastCanShootTarget = false;
	void UpdateCanShootTarget();
	
	bool bLastIsCloseToPlayer = false;
	void UpdateIsCloseToPlayer();
	
	bool bLastIsGameOver = false;
	void UpdateIsGameOver();

	/** 
	 * This method is required becase Posesses method is called lated 
	 * than BeginPlay when you spawn AI pawns in runtime 
	 */
	void EnsurePropertiesInitialized();
	bool bIsBlackboardReady = false;

	void OnBlackboardInitialized();
	bool bIsInitialized = false;
};
