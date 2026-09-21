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
	void UpdateBlackboardHealth(float Ratio);                                                                           // Updates the Health value in the AI Blackboard.

	UFUNCTION() void UpdateBlackboardAmmo(float Current, float Max);                                                    // Updates the Ammo values in the AI Blackboard.

protected:
	// Don't forget to set the WeaponClass to BP_CodeBaseRifle in the editor (and not the ABaseRifle class)

	UPROPERTY(EditDefaultsOnly, Category = Default) FName TintName;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName ActionStoppedMessage;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName HealthRatioKey;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName MaxAmmoKey;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName CurrentAmmoKey;
	UPROPERTY(EditDefaultsOnly, Category = Default) FLinearColor Color;

	void PostLoad() override;                                                                                           // Called after loading the level and starting the game; runs before BeginPlay.

	virtual void BeginPlay() override;                                                                                  // Called when the game starts or when spawned.

	virtual void HandleHurt(float Ratio) override;                                                                      // Triggers the hit animation for the AAgent and updates the Health in the AI Blackboard.
	virtual void HandleMuerte(float Ratio) override;                                                                    // Triggers the death animation for the AAgent.

public:
	AAgent();                                                                                                           // Ctor that sets default values for AAgent.

	UFUNCTION() void HandleActionFinished();                                                                            // Sends a message to the UBTTaskNode to indicate the completion of a certain behavior.

	//----------------------------------------------------------------------//
	// IEnemyBehaviorsInterface
	//----------------------------------------------------------------------//
	virtual void EnemyAttack() override;                                                                                // Allows the enemy to fire ABaseRifle.
	virtual void EnemyReload() override;                                                                                // Allows the enemy to request a reload to the ABaseRifle's ammo.
};
