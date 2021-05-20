// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>

#include "Tools/MacroTools.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BackToMenuButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnBackButtonPressedResult);
}

void UGameOverWidget::SetVictoryResult(EDefenceGameModeResult Result)
{
	switch (Result)
	{
	case EDefenceGameModeResult::Victory:
		GameOverResultVictory->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		GameOverResultDefeat->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EDefenceGameModeResult::Defeat:
		GameOverResultDefeat->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		GameOverResultVictory->SetVisibility(ESlateVisibility::Collapsed);
		break;

	default:
		EnsureMsg(false, TEXT("[GameOverWidget] Undefined game over result"));
	}
}

void UGameOverWidget::OnBackButtonPressedResult()
{
	OnBackButtonPressed.Broadcast();
}
