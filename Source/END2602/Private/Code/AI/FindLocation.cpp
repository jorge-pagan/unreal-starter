// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AI/FindLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindLocation::UFindLocation() : KeyName("Location") {}

EBTNodeResult::Type UFindLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type r = EBTNodeResult::Failed;

	UObject* World = GetWorld();
	if (UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(World))
	{
		FVector RandomLocation;
		r = NavSys->K2_GetRandomLocationInNavigableRadius(World, OwnerComp.GetAIOwner()->K2_GetActorLocation(),
			RandomLocation, Radius) ? EBTNodeResult::Succeeded : r;

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(KeyName, RandomLocation);

		FinishLatentTask(OwnerComp, r);
	}
	else UE_LOG(FindLocation, Warning, TEXT("No navigation system present in the world!"));

	return r;
}
