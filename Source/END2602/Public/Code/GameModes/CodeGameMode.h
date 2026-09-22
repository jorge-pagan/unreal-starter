// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "Code/Widgets/ResultsHUD.h"
#include "Code/Actors/BasePlayer.h"
#include "Code/Interfaces/WinConditionInterface.h"

#include "CodeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API ACodeGameMode : public AGameModeBase, public IWinConditionInterface
{
	GENERATED_BODY()

private:
	ABasePlayer* CurrentPlayer;
	UResultsHUD* ResultsWidgetObject;

	// Checks for the win condition
	UFUNCTION() void RemoveEnemy(AActor* DestroyedActor);

	UFUNCTION() void RemovePlayer();
protected:
	int32 NumberOfEnemies;
	UPROPERTY(EditDefaultsOnly) EMouseLockMode PlayerLoseMenuMouseLockType = EMouseLockMode::LockAlways;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<UUserWidget> ResultsWidgetClass;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<AActor> BaseCharacterClass;

	virtual void BeginPlay() override;

public:
	ACodeGameMode();

	virtual void AddEnemy(AActor* OtherActor) override;
};
