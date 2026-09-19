// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Instances/CodeGameInstance.h"
#include "../END2602.h"

void UCodeGameInstance::LoadLevel(int32 LevelIndex)
{
	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(CodeGameInstance, Error, TEXT("Failed to retrieve world!"));
		return;
	}
	else if (!GEngine)
	{
		UE_LOG(CodeGameInstance, Error, TEXT("GEngine is nullptr!"));
		return;
	}

	// Setting travel type and retrieving World Context
	const ETravelType TravelType = TRAVEL_Absolute;

	// Retrieving level name
	if (GameLevels.Num() == 0)
	{
		UE_LOG(CodeGameInstance, Error, TEXT("No levels are present in the GameLevels array from the GameInstance!"));
		return;
	}

	FString LevelName = GameLevels[LevelIndex].ToString();

	// Verifying the level exists if it's a local file
	FURL TestURL(&WorldContext->LastURL, *LevelName, TravelType);
	if (TestURL.IsLocalInternal() && !GEngine->MakeSureMapNameIsValid(TestURL.Map))
	{
		UE_LOG(CodeGameInstance, Error, TEXT("The level \"%s\" could not be found!"), *TestURL.Map);
		return;
	}
	CurrentLevel = LevelIndex;

	// Allows the client to travel to the level.
	GEngine->SetClientTravel(World, *LevelName, TravelType);
}

void UCodeGameInstance::LoadLevelSafe(int32 LevelIndex)
{
	if (GameLevels.IsValidIndex(LevelIndex)) LoadLevel(LevelIndex);
	else UE_LOG(CodeGameInstance, Error, TEXT("The level index (%i) is not a valid index in the game instance!"), CurrentLevel);
}

void UCodeGameInstance::ReloadLevel()
{
	LoadLevelSafe(CurrentLevel);
}

void UCodeGameInstance::QuitToMenu()
{
	LoadLevelSafe(MainMenuIndex);
}

void UCodeGameInstance::QuitTheGame()
{
	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(CodeGameInstance, Error, TEXT("Failed to retrieve world!"));
		return;
	}
	else if (World->GetGameInstance() != this) // Also checks if GameInstance is nullptr. "this" can never be nullptr.
	{
		UE_LOG(CodeGameInstance, Error, TEXT("Failed to retrieve game instance or not using the same game instance!"));
	}

	// Retrieve the controller and send the shutdown command to it
	for (ULocalPlayer* LP : LocalPlayers)
	{
		if (APlayerController* PC = LP->PlayerController)
		{
			PC->ConsoleCommand("quit force");
			return;
		}
	}
}