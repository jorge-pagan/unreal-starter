// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "AgentController.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API AAgentController : public AAIController
{
	GENERATED_BODY()

private:
	UAISenseConfig_Sight* SenseConfig;

	void OnPossess(APawn* InPawn) override;
	
	UFUNCTION() void HandlePerception(AActor* ActorInView, FAIStimulus Stimulus);

protected:
	UPROPERTY(EditDefaultsOnly) UBehaviorTree* BTAsset;
	UPROPERTY(EditDefaultsOnly) FName PlayerKey;
public:
	AAgentController();

	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
};