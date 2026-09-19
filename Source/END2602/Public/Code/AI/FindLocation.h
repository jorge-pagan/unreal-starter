// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BTTaskNode.h"
#include "../END2602.h"

#include "FindLocation.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API UFindLocation : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = Default) float Radius = 300.f;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName KeyName;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UFindLocation();
};
