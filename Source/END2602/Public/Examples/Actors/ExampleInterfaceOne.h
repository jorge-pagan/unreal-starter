// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ExampleInterfaceOne.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UExampleInterfaceOne : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class END2602_API IExampleInterfaceOne
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION() virtual void TestFunction() = 0;

	UFUNCTION(BlueprintCallable) virtual void BlueprintCallable_Sept();
};
