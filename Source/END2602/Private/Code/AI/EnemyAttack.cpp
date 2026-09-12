// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AI/EnemyAttack.h"
#include "AIController.h"
#include "EngineUtils.h"

EBTNodeResult::Type UEnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (IEnemyBehaviorsInterface* I = Cast<IEnemyBehaviorsInterface>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		I->EnemyAttack();
		WaitForMessage(OwnerComp, ActionFinishedMessage);
		
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}