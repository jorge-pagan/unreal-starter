// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleVariables.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateType, AActor*, OtherActor);

UCLASS()
class END2602_API AExampleVariables : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExampleVariables();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables|ReadOnly")
	bool VisibleAnywhere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Variables|ReadOnly")
	uint8 VisibleDefaultsOnly = 10;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Variables|ReadOnly")
	int32 VisibleInstanceOnly;

	UPROPERTY(VisibleInstanceOnly, Category = "Variables|ReadOnly")
	int64 VisibleInstanceOnlyOdd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables|ReadWrite")
	float EditAnywhere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables|ReadWrite")
	FName EditDefaultsOnly;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Variables|ReadWrite")
	FString EditInstanceOnly;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables|ReadWrite")
	FText EditDefaultsOnlyOdd;

	UPROPERTY(EditInstanceOnly, Category = "Variables|ReadWrite")
	FText EditInstanceOnlyOdd;

	//Class Reference
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables|ClassReference")
	TSubclassOf<AActor> ClassType;

	//Create a Variable of the delegate/ Event Dispatcher
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Variables")
	FDelegateType OnDelegateInstance;

private:
	UFUNCTION()
	void ExampleBoundFunction(AActor* other);

	UFUNCTION()
	void AnotherExampleBoundFunction(AActor* other);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables|Array")
	TArray<int32> ValueArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables|Array")
	TArray<UObject*> PointerArray;
};
