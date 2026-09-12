// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/DamagePickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API AHealthPickup : public ADamagePickup
{
	GENERATED_BODY()

protected:
	virtual void PostPickup() override;
};
