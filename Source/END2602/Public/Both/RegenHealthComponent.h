// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Both/HealthComponent.h"
#include "RegenHealthComponent.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API URegenHealthComponent : public UHealthComponent
{
	GENERATED_BODY()

private:
	FTimerHandle RegenTimerHandle;

protected:
	virtual void HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser) override;

	UFUNCTION() void HandleDeath(float Value);

public:
	URegenHealthComponent();

	void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION() void TurnTickOff();
	UFUNCTION() void TurnTickOn();
};
