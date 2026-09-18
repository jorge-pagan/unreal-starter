// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Code/Actors/BaseCharacter.h"
#include "Both/PlayerHUD.h"

#include "BasePlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerLost);

/**
 *
 */
UCLASS()
class END2602_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()

private:
	APlayerController* PlayerController;

	void InputAxisStrafe(float AxisValue);                                                                              // Allows ABasePlayer to move left or right; strafing.
	void InputAxisMoveForward(float AxisValue);                                                                         // Allows ABasePlayer to move forwards and backwards.

	void Fire();                                                                                                        // Fires ABasePlayer's rifle.
	inline void Reload() { BaseRifle->RequestReload(); }                                                                // Requests a reload to the ABaseRifle's ammo.
	UFUNCTION() void PlayerLost();                                                                                      // Broadcasts ABasePlayer's OnPlayerLost delegate and disables the HUD after losing.

protected:
	UPROPERTY(VisibleAnywhere, Category = Character) class USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, Category = Character) FVector SpringArmRelativeLocation;
	UPROPERTY(EditDefaultsOnly, Category = Character) float TargetArmLength;
	UPROPERTY(VisibleAnywhere, Category = Character) class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = HUD) TSubclassOf<UUserWidget> HUDClass;
	UPROPERTY(VisibleAnywhere, Category = HUD) UPlayerHUD* HUDObject;

	virtual void BeginPlay() override;                                                                                  // Called when the game starts or when spawned

public:
	ABasePlayer();                                                                                                      // Ctor that sets default values for ABasePlayer.
	
	UPROPERTY(EditDefaultsOnly, Category = Default) FOnPlayerLost OnPlayerLost;

	void PlayerWon();                                                                                                   // Broadcasts ABasePlayer's OnPlayerLost delegate and disables the HUD after winning.

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;                       // Called to bind functionality to input.

	virtual FRotator GetBaseAimRotation() const override;                                                               // Rotation matrix to rotate the projectile from the rifle to the UPlayerHUD's Crosshair.

	//----------------------------------------------------------------------//
	// IPickupQueriesInterface
	//----------------------------------------------------------------------//
    virtual bool CanPickupHealth() const override;                                                                      // Decides whether or not ABasePlayer is allowed to use the health pickup.
};
