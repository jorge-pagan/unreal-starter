// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleFunctions.generated.h"

UCLASS()
class END2602_API AExampleFunctions : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExampleFunctions();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Declare in C++, define in C++, call in C++ and/or Blueprints
	UFUNCTION(BlueprintCallable)
	void BlueprintCallable();

	// Declare in C++, define in Blueprints, call in C++ and/or Blueprints
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BlueprintImplementableEvent();

	//Blueprint Native Event - Declare in C++, define in Blueprint and in C++, 
	//								but in C++ have to add _Implementation to the definition
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BlueprintNativeEvent();

	UFUNCTION(BlueprintCallable)
	float PureFunction() const;

	//Multi Return Values
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool MultipleReturnValues(AActor* Actor1, FRotator Rotation, AActor*& Actor2, int32& Index);
};
