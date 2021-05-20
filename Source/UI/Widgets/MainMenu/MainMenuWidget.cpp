// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include <Components/Button.h>

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayButtonClicked);
}

void UMainMenuWidget::OnPlayButtonClicked()
{
	OnPlayClicked.Broadcast();

	/* Double click protection */
	PlayButton->SetIsEnabled(false);
}
