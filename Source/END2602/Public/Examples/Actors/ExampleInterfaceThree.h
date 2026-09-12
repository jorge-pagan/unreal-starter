// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ExampleInterfaceThree.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UExampleInterfaceThree : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class END2602_API IExampleInterfaceThree
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void BlueprintNativeEvent_Sept(); // Only call this one from the driver code

	virtual void BlueprintNativeEvent_Sept_Implementation(); // ensures only the C++ implementation is invoked (ignores the blueprint side)
};
