// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/GameModes/CodeGameMode.h"
#include "Code/Controllers/GamePlayerController.h"
#include "Code/Actors/BasePlayer.h"

ACodeGameMode::ACodeGameMode()
{
	PlayerControllerClass = AGamePlayerController::StaticClass();
	DefaultPawnClass = ABasePlayer::StaticClass();
}