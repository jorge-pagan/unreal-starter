// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Code/Actors/BasePickup.h"
#include "Particles/ParticleSystemComponent.h"

#include "DamagePickup.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API ADamagePickup : public ABasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly) float DamageAmount;
	UPROPERTY(EditDefaultsOnly) UParticleSystemComponent* ParticleSystem;

	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override;
	virtual void PostPickup() override;

public:
	ADamagePickup();
};
