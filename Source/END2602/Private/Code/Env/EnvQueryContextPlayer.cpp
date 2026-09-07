// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Env/EnvQueryContextPlayer.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EngineUtils.h"

void UEnvQueryContextPlayer::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	UWorld* World = GetWorld();
	if (BlueprintSubclass)
	{
		if (TActorIterator<AActor> It(World, BlueprintSubclass); It)
		{
			AActor* ResultingBPActor = *It;
			UEnvQueryItemType_Actor::SetContextHelper(ContextData, ResultingBPActor);
			return;
		}
	}
	
	if (CodeSubclass)
	{
		if (TActorIterator<AActor> It(World, CodeSubclass); It)
		{
			AActor* ResultingCodeActor = *It;
			UEnvQueryItemType_Actor::SetContextHelper(ContextData, ResultingCodeActor);
			return;
		}
	}
	else UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(QueryInstance.Owner.Get()));

	// How to return...
}