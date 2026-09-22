// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WinConditionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWinConditionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class END2602_API IWinConditionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AddEnemy(AActor* OtherActor) = 0;
};
