// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyBehaviors.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyBehaviorsInterface : public UInterface
{
	GENERATED_BODY()
};


class END2602_API IEnemyBehaviorsInterface
{
	GENERATED_BODY()

public:
	UFUNCTION() virtual void EnemyAttack() = 0;
	UFUNCTION() virtual void EnemyReload() = 0;
};