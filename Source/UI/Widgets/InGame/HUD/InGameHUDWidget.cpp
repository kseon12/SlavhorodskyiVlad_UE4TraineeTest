// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUDWidget.h"

#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>

void UInGameHUDWidget::SetDefenceTimerValue(float ValueInSeconds)
{
	static const int64 SecondsInMinute = ETimespan::TicksPerMinute / ETimespan::TicksPerSecond;
	int64 RemainingTimeInSeconds = static_cast<int64>(ValueInSeconds);
		
	int64 MinutesLeft = RemainingTimeInSeconds / SecondsInMinute;
	int64 SecondsLeft = RemainingTimeInSeconds - (MinutesLeft * SecondsInMinute);

	FString UpTo10MinutesCharacter = IsNumberUpTo10(MinutesLeft) ? "0" : "";
	FString UpTo10SecondsCharacter = IsNumberUpTo10(SecondsLeft) ? "0" : "";
		
	FString TimeResultStr = UpTo10MinutesCharacter + FString::FromInt(MinutesLeft) + ":" + UpTo10SecondsCharacter + FString::FromInt(SecondsLeft);

	DefenceTimer->SetText(FText::FromString(TimeResultStr));
}

void UInGameHUDWidget::SetMissionInfo(const FString& Info)
{
	MissionInfo->SetText(FText::FromString(Info));
}

void UInGameHUDWidget::SetCurrentWeaponName(const FString& Name)
{
	CurrentWeapon->SetText(FText::FromString(Name));
}

void UInGameHUDWidget::SetCurrentHealth(float Value)
{
	CurrentHealth->SetPercent(Value);
	FString HealthTextString = FString::Printf(TEXT("%i"),(int)Value)+TEXT("%");
	HealthText->SetText(FText::FromString(HealthTextString));
}

bool UInGameHUDWidget::IsNumberUpTo10(int32 Number) const
{
	return Number < 10;
}

