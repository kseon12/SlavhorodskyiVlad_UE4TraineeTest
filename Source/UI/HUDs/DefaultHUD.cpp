// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultHUD.h"

#include "UI/Widgets/DefaultUserWidget.h"
#include "UI/Controllers/WidgetController.h"

#include "Tools/MacroTools.h"

void ADefaultHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!EnsureMsg(MainWidgetClass && MainWidgetControllerClass, 
		TEXT("[DefaultHUD] MainWidgetClass or MainWidgetControllerClass is not set")))
	{
		return;
	}

	MainWidget = CreateWidget<UDefaultUserWidget>(GetWorld(), MainWidgetClass);
	MainWidget->AddToViewport();

	MainController = NewObject<UWidgetController>(this, MainWidgetControllerClass);
	MainController->Initialize(MainWidget);
}
