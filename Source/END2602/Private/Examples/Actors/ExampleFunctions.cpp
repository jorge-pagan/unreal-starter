// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/Actors/ExampleFunctions.h"
#include "../END2602.h"

// Sets default values
AExampleFunctions::AExampleFunctions()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExampleFunctions::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(Game, Log, TEXT("in Begin Play"));
	BlueprintImplementableEvent();
	UE_LOG(Game, Log, TEXT("Just Called Blueprint Native Event from C++"));
	BlueprintNativeEvent();
	UE_LOG(Game, Log, TEXT("Just Called Blueprint Native Event _Implementation from C++"));
	BlueprintNativeEvent_Implementation();
}

// Called every frame
void AExampleFunctions::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExampleFunctions::BlueprintCallable()
{
	UE_LOG(Game, Log, TEXT("Blueprint Callable"));
}

float AExampleFunctions::PureFunction() const
{
	return 3.14f;
}

void AExampleFunctions::BlueprintNativeEvent_Implementation()
{
	UE_LOG(Game, Warning, TEXT("Blueprint Native Event was called in C++"));
}

//void AExampleFunctions::BlueprintImplementableEvent()
//{
//	UE_LOG(Game, Log, TEXT("Blueprint Implementable Event"));
//}

