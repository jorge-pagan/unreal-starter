// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseCharacter.h"
#include "Code/Interfaces/EnemyAttackInterface.h"

#include "Agent.generated.h"

/**
 *
 */
UCLASS()
class END2602_API AAgent : public ABaseCharacter, public IEnemyAttackInterface
{
	GENERATED_BODY()

public:
	AAgent();

	virtual void Tick(float DeltaTime) override;
protected:
	// Don't forget to set the WeaponClass to BP_CodeBaseRifle in the editor (and not the ABaseRifle class)

	UPROPERTY(EditDefaultsOnly, Category = Default) FName TintName;
	UPROPERTY(EditDefaultsOnly, Category = Default) FLinearColor Color;
	UPROPERTY(EditDefaultsOnly, Category = Default) int MaterialIndex;

	void PostLoad() override;


	//----------------------------------------------------------------------//
	// IEnemyAttackInterface
	//----------------------------------------------------------------------//
	virtual void EnemyAttack() override;

};
