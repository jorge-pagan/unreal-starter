// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "../END2602.h"

#include "AgentController.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API AAgentController : public AAIController
{
	GENERATED_BODY()

public:
	AAgentController();

private:

	UPROPERTY(EditDefaultsOnly, Category = Default) UBehaviorTree* BTAsset;
	UPROPERTY(EditDefaultsOnly, Category = Default) UAIPerceptionComponent* AIPerception;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName PlayerKey;

	void OnPossess(APawn* InPawn) override;
	UFUNCTION() void HandlePerception(AActor* ActorInView, FAIStimulus Stimulus);
};
