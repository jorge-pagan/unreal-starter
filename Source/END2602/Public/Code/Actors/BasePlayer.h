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

	void InputAxisStrafe(float AxisValue);
	void InputAxisMoveForward(float AxisValue);

	void Fire();
	void Reload();
	UFUNCTION() void PlayerLost();

protected:
	UPROPERTY(VisibleAnywhere, Category = Character) class USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, Category = Character) FVector SpringArmRelativeLocation;
	UPROPERTY(EditDefaultsOnly, Category = Character) float TargetArmLength;
	UPROPERTY(VisibleAnywhere, Category = Character) class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = HUD) TSubclassOf<UUserWidget> HUDClass;
	UPROPERTY(VisibleAnywhere, Category = HUD) UPlayerHUD* HUDObject;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ABasePlayer();

	void PlayerWon();
	UPROPERTY(EditDefaultsOnly, Category = Default) FOnPlayerLost OnPlayerLost;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FRotator GetBaseAimRotation() const override;

	//----------------------------------------------------------------------//
	// IPickupQueriesInterface
	//----------------------------------------------------------------------//
    virtual bool CanPickupHealth() const override;
};
