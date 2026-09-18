// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"

#include "CodeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API ACodeGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	ABasePlayer* CurrentPlayer;

	// Checks for the win condition
	UFUNCTION() void RemoveEnemy(AActor* DestroyedActor);

protected:
	int32 NumberOfEnemies;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<AActor> BaseCharacterClass;

	virtual void BeginPlay() override;

public:
	ACodeGameMode();
};
