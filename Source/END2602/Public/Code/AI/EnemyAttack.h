// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/Agent.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include "EnemyAttack.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API UEnemyAttack : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Default) FName ActionFinishedMessage;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};