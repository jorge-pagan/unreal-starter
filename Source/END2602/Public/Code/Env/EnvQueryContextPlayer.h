// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvQueryContextPlayer.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API UEnvQueryContextPlayer : public UEnvQueryContext
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Default) TSubclassOf<AActor> BlueprintSubclass;
	UPROPERTY(EditDefaultsOnly, Category = Default) TSubclassOf<AActor> CodeSubclass;

	void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
