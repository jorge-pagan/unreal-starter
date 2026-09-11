// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AI/EnemyReload.h"
#include "Code/Actors/Agent.h"
#include "EngineUtils.h"

EBTNodeResult::Type UEnemyReload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	for (TActorIterator<AAgent> It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;

		if (IEnemyBehaviorsInterface* I = Cast<IEnemyBehaviorsInterface>(Actor))
		{
			I->EnemyReload();

			OwnerComp.RegisterMessageObserver(this, ActionFinishedMessage);

			return EBTNodeResult::InProgress;
		}
	}

	return EBTNodeResult::Failed;
}