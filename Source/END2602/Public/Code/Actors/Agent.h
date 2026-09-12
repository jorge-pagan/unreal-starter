// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Code/Actors/BaseCharacter.h"
#include "Code/Interfaces/EnemyBehaviors.h"

#include "Agent.generated.h"

/**
 *
 */
UCLASS()
class END2602_API AAgent : public ABaseCharacter, public IEnemyBehaviorsInterface
{
	GENERATED_BODY()

private:
	void UpdateBlackboardHealth(float Ratio);

	UFUNCTION() void UpdateBlackboardAmmo(float Current, float Max);

protected:
	// Don't forget to set the WeaponClass to BP_CodeBaseRifle in the editor (and not the ABaseRifle class)

	UPROPERTY(EditDefaultsOnly, Category = Default) FName TintName;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName ActionStoppedMessage;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName HealthRatioKey;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName AmmoKey;
	UPROPERTY(EditDefaultsOnly, Category = Default) FLinearColor Color;
	UPROPERTY(EditDefaultsOnly, Category = Default) int MaterialIndex;

	void PostLoad() override;

	virtual void BeginPlay() override;

	virtual void HandleHurt(float Ratio) override;

public:
	AAgent();

	UFUNCTION() void HandleActionFinished();

	//----------------------------------------------------------------------//
	// IEnemyBehaviorsInterface
	//----------------------------------------------------------------------//
	virtual void EnemyAttack() override;
	virtual void EnemyReload() override;
};
