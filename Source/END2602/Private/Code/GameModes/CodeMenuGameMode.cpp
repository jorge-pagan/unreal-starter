// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/GameModes/CodeMenuGameMode.h"
#include "Code/Controllers/MenuPlayerController.h"

ACodeMenuGameMode::ACodeMenuGameMode()
{
	PlayerControllerClass = AMenuPlayerController::StaticClass();
}