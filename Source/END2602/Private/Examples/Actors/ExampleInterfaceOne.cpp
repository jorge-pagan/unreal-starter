// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/Actors/ExampleInterfaceOne.h"
#include "../END2602.h"

// Add default functionality here for any IExampleInterfaceOne functions that are not pure virtual.

void IExampleInterfaceOne::BlueprintCallable_Sept()
{
	UE_LOG(Game, Warning, TEXT("---> I made it into the BlueprintCallable function!"));
}