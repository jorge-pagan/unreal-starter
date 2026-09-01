// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/Actors/ExampleVariables.h"
#include "../END2602.h"

// Sets default values
AExampleVariables::AExampleVariables()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ValueArray.Add(3);
	ValueArray.Add(4);
	PointerArray.Add(this);
	PointerArray.Add(nullptr);
}

// Called when the game starts or when spawned
void AExampleVariables::BeginPlay()
{
	Super::BeginPlay();
	
	//This is how C++ does the bind in BLueprint
	//Params send into AddDynamic are the same thing as created in Blueprint
	//As seen in Base Character Begin Play
	OnDelegateInstance.AddDynamic(this, &AExampleVariables::ExampleBoundFunction);
	OnDelegateInstance.AddDynamic(this, &AExampleVariables::AnotherExampleBoundFunction);

	OnDelegateInstance.Broadcast(this);
}

// Called every frame
void AExampleVariables::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExampleVariables::ExampleBoundFunction(AActor* other)
{
	UE_LOG(Game, Error, TEXT("Function called by Delegate"));
}

void AExampleVariables::AnotherExampleBoundFunction(AActor* other)
{
	UE_LOG(Game, Error, TEXT("Another Function called by Delegate"));
}

