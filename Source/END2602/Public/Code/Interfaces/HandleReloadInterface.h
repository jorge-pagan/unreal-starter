// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HandleReloadInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHandleReloadInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class END2602_API IHandleReloadInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void HandleReloadEnded() = 0;
	virtual void HandleReloadNow() = 0;
};
