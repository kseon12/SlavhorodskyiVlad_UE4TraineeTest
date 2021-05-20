// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyAnalyzerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEDEFENDER_API UEnemyAnalyzerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UEnemyAnalyzerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	bool CanShootCurrentTarget() const { return bCanShootTarget; }

protected:
	
	/** How often we should check on ability to shoot the target */
	UPROPERTY(EditAnywhere)
	float CheckOnCanShootEvery = 1.0f;

	virtual void BeginPlay() override;

private:

	void CheckCanShootCurrentTarget();

	bool bCanShootTarget = false;
	float CheckTimer = 0.0f;
};
