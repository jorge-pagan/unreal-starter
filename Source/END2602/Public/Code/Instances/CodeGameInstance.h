// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CodeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API UCodeGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	int32 CurrentLevel;
	UPROPERTY(EditDefaultsOnly) int32 FirstLevelIndex = 1;
	UPROPERTY(EditDefaultsOnly) TArray<FName> GameLevels;

public:
	void LoadLevel(int32 LevelIndex);
	void LoadLevelSafe(int32 LevelIndex);
	UFUNCTION() inline void LoadFirstLevel() { LoadLevelSafe(FirstLevelIndex); }
	UFUNCTION() void QuitTheGame();
};
