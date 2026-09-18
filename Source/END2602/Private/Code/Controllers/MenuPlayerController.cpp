// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Controllers/MenuPlayerController.h"
#include "Code/Widgets/MainMenuHUD.h"

AMenuPlayerController::AMenuPlayerController() : 
	MenuClass(UMainMenuHUD::StaticClass())
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bShowMouseCursor = true;
}

void AMenuPlayerController::BeginPlay()
{
	if (UMainMenuHUD* MainMenu = CreateWidget<UMainMenuHUD>(this, MenuClass, ""))
	{
		// Adding the MainMenuHUD to the viewport
		MainMenu->AddToViewport();

		// Locking the mouse to the MainMenu widget
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(MouseLockType);
		InputMode.SetWidgetToFocus(MainMenu->TakeWidget());
	
		// Setting the input mode and flushing any pressed keys after level travel is complete.
		SetInputMode(InputMode);
		FlushPressedKeys();
	}
}