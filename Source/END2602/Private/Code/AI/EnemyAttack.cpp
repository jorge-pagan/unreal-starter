// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AI/EnemyAttack.h"
#include "EngineUtils.h"

EBTNodeResult::Type UEnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	for (TActorIterator<AAgent> It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;

		if (IEnemyBehaviorsInterface* I = Cast<IEnemyBehaviorsInterface>(Actor))
		{
			I->EnemyAttack();

			OwnerComp.RegisterMessageObserver(this, ActionFinishedMessage);

			return EBTNodeResult::InProgress;
		}
	}

	return EBTNodeResult::Failed;
}