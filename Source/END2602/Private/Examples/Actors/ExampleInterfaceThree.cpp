// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/Actors/ExampleInterfaceThree.h"
#include "../END2602.h"

// Add default functionality here for any IExampleInterfaceThree functions that are not pure virtual.

void IExampleInterfaceThree::BlueprintNativeEvent_Sept_Implementation()
{
	UE_LOG(Game, Warning, TEXT("..........I made it into the BlueprintNativeEvent! (GrandParent)"));
}
