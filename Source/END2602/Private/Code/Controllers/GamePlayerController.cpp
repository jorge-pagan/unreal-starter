// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Controllers/GamePlayerController.h"

void AGamePlayerController::BeginPlay()
{
	// Setting the input mode to GameOnly and flushing any pressed keys after level travel is complete.
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	FlushPressedKeys();
}