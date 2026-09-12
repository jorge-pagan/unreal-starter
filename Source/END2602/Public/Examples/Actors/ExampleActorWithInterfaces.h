// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleInterfaceOne.h"
#include "ExampleInterfaceThree.h"
#include "../END2602.h"

#include "ExampleActorWithInterfaces.generated.h"

UCLASS()
class END2602_API AExampleActorWithInterfaces : public AActor, public IExampleInterfaceOne, public IExampleInterfaceThree
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExampleActorWithInterfaces();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//! INCLUDE THIS INTERFACE COMMENT BLOCK
	//----------------------------------------------------------------------//
	// IExampleInterfaceOne
	//----------------------------------------------------------------------//
	virtual void TestFunction() override;

	//----------------------------------------------------------------------//
	// IExampleInterfaceThree
	//----------------------------------------------------------------------//
	virtual void BlueprintNativeEvent_Sept_Implementation() override;
};
