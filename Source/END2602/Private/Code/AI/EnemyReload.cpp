// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AI/EnemyReload.h"
#include "Code/Actors/Agent.h"
#include "AIController.h"
#include "EngineUtils.h"

EBTNodeResult::Type UEnemyReload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (IEnemyBehaviorsInterface* I = Cast<IEnemyBehaviorsInterface>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		I->EnemyReload();
		WaitForMessage(OwnerComp, ActionFinishedMessage);

		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}