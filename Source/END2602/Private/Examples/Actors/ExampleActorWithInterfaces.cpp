// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/Actors/ExampleActorWithInterfaces.h"

// Sets default values
AExampleActorWithInterfaces::AExampleActorWithInterfaces()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExampleActorWithInterfaces::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExampleActorWithInterfaces::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExampleActorWithInterfaces::TestFunction()
{
	UE_LOG(Game, Warning, TEXT("Hey, I made it into the TestFunction!"));
}

void AExampleActorWithInterfaces::BlueprintNativeEvent_Sept_Implementation()
{
	UE_LOG(Game, Warning, TEXT(",,,,,,,,,,I made it into the BlueprintNativeEvent! (Parent)"));
}
