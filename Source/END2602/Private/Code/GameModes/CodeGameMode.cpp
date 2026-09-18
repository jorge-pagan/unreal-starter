// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/GameModes/CodeGameMode.h"
#include "Code/Controllers/GamePlayerController.h"
#include "Code/Actors/BasePlayer.h"
#include "../END2602.h"

ACodeGameMode::ACodeGameMode() : BaseCharacterClass(ABaseCharacter::StaticClass()), NumberOfEnemies(0)
{
	PlayerControllerClass = AGamePlayerController::StaticClass();
	DefaultPawnClass = ABasePlayer::StaticClass();
}

void ACodeGameMode::RemoveEnemy(AActor* DestroyedActor)
{
	NumberOfEnemies = FMath::Max(0, NumberOfEnemies - 1);
	if (NumberOfEnemies > 0)
	{

	}
	else
	{
		UE_LOG(Game, Warning, TEXT("You win!!!"));
	}
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
				}
				else
				{
					++NumberOfEnemies;
					Actor->OnDestroyed.AddDynamic(this, &ACodeGameMode::RemoveEnemy);
				}
			}

		}
		else UE_LOG(Game, Warning, TEXT("Failed to retrieve World!"));
	}
	else UE_LOG(Game, Warning, TEXT("BaseCharacterClass is not initialized!"));
}