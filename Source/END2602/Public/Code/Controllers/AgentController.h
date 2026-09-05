// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default) UBehaviorTree* BTAsset;

	void OnPossess(APawn* InPawn) override;
};
