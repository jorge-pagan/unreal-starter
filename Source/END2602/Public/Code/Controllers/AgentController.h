// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"

#include "AgentController.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API AAgentController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = Default) UBehaviorTree* BTAsset;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName PlayerKey;

	void OnPossess(APawn* InPawn) override;

	UFUNCTION() void HandlePerception(AActor* ActorInView, FAIStimulus Stimulus);

public:
	AAgentController();
};