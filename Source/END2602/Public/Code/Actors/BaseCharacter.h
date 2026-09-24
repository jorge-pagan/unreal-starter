// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../../Both/CharacterAnimation.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "Both/HealthComponent.h"
#include "Code/Actors/BaseRifle.h"
#include "Code/Interfaces/PickupQueriesInterface.h"

#include "BaseCharacter.generated.h"

UCLASS(Abstract)
class END2602_API ABaseCharacter : public ACharacter, public IPickupQueriesInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;                                                                                  // Called when the game starts or when spawned.

	UPROPERTY(EditDefaultsOnly, Category = Default) UChildActorComponent* BaseRifleChildComponent;                    
	UPROPERTY(EditDefaultsOnly, Category = Default) ABaseRifle* BaseRifle;
	UPROPERTY(EditDefaultsOnly, Category = Default) TSubclassOf<AActor> WeaponClass;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName WeaponSocketName;
	UPROPERTY(EditDefaultsOnly, Category = Default) UCharacterAnimation* AnimInstance;
	UPROPERTY(EditDefaultsOnly, Category = Default) UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, Category = TeamID) FGenericTeamId TeamID = -1;

	UFUNCTION() virtual void HandleHurt(float NotUsed);                                                                 // Triggers the hit animation for the ABaseCharacter.
	UFUNCTION() virtual void HandleMuerte(float NotUsed);                                                               // Triggers the death animation and disables input for the ABaseCharacter.

public:
	ABaseCharacter();                                                                                                   // Ctor that sets default values for ABaseCharacter.

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;                       // Called to bind functionality to the input.

	inline virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; }                                  // Retrieves the TeamID
	inline virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override { TeamID = NewTeamID; }              // Changes the TeamID

	//----------------------------------------------------------------------//
	// IPickupQueriesInterface
	//----------------------------------------------------------------------//
	virtual bool CanPickupHealth() const override;                                                                      // Decides whether or not ABaseCharacter is allowed to use the health pickup.
	virtual bool CanPickupMaxAmmo() const override;                                                                     // Decides whether or not ABaseCharacter is allowed to use the max ammo pickup.

	virtual void IncreaseMaxAmmo(float Increment) override;                                                             // Increases the max capacity of ABaseRifle.
};
