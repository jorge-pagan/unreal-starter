// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/GameModes/CodeGameMode.h"
#include "Code/Controllers/GamePlayerController.h"
#include "Code/Actors/BasePlayer.h"
#include "../END2602.h"
#include "EngineUtils.h"

ACodeGameMode::ACodeGameMode() : BaseCharacterClass(ABaseCharacter::StaticClass()), 
ResultsWidgetClass(UResultsHUD::StaticClass()), NumberOfEnemies(0)
{
	PlayerControllerClass = AGamePlayerController::StaticClass();
	DefaultPawnClass = ABasePlayer::StaticClass();
}

void ACodeGameMode::RemoveEnemy(AActor* DestroyedActor)
{
	NumberOfEnemies = FMath::Max(0, NumberOfEnemies - 1);
	if (NumberOfEnemies == 0)
	{
		ResultsWidgetObject->WinConditionMet();
		ResultsWidgetObject->AddToViewport();
		CurrentPlayer->PlayerWon();

		UE_LOG(Game, Warning, TEXT("You win!!!"));
	}
}

void ACodeGameMode::RemovePlayer()
{
	ResultsWidgetObject->AddToViewport();
	
	// Locking the mouse to the Results Widget
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(PlayerLoseMenuMouseLockType);
	InputMode.SetWidgetToFocus(ResultsWidgetObject->TakeWidget());

	// Setting the input mode and flushing any pressed keys after menu loads
	ResultsWidgetObject->GetOwningPlayer()->SetInputMode(InputMode);
	ResultsWidgetObject->GetOwningPlayer()->FlushPressedKeys();

	UE_LOG(Game, Warning, TEXT("You suck!!!"));
}

void ACodeGameMode::BeginPlay()
{
	if (BaseCharacterClass)
	{
		if (UWorld* World = GetWorld())
		{
			TArray<AActor*> ActorArray;
			for (TActorIterator<AActor> It(World, BaseCharacterClass); It; ++It)
			{
				AActor* Actor = *It;
				ActorArray.Add(Actor);
			}

			for (AActor* Actor : ActorArray)
			{
				if (ABasePlayer* BP = Cast<ABasePlayer>(Actor))
				{
					CurrentPlayer = BP;
					CurrentPlayer->OnPlayerLost.AddDynamic(this, &ACodeGameMode::RemovePlayer);
				}
				else
				{
					++NumberOfEnemies;
					Actor->OnDestroyed.AddDynamic(this, &ACodeGameMode::RemoveEnemy);
				}
			}

			if (TActorIterator<AActor> It(World, PlayerControllerClass); It)
			{
				APlayerController* PC = Cast<APlayerController>(*It);
				if (UResultsHUD* ResultsHUD = CreateWidget<UResultsHUD>(PC, ResultsWidgetClass))
				{
					ResultsWidgetObject = ResultsHUD;
				}
			}
		}
		else UE_LOG(Game, Warning, TEXT("Failed to retrieve World!"));
	}
	else UE_LOG(Game, Warning, TEXT("BaseCharacterClass is not initialized!"));
}