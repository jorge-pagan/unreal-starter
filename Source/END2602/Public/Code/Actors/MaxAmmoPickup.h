// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Code/Actors/BasePickup.h"

#include "MaxAmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API AMaxAmmoPickup : public ABasePickup
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly) float IncreaseAmount = 1;
	UPROPERTY(EditDefaultsOnly) UStaticMeshComponent* Mesh;

protected:
	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override;
	virtual bool CanPickup(AActor* OtherActor) const override;

public:
	AMaxAmmoPickup();
};
