// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"

ABasePlayer::ABasePlayer()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetRelativeLocation(FVector(0.0f, 80.0f, 90.0f));
	SpringArm->SetupAttachment(GetRootComponent());
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind Rotation Functions
	PlayerInputComponent->BindAxis("TurnRight", this, &ABasePlayer::AddControllerYawInput);

	//Bind Movement Functions
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::InputAxisMoveForward);
}

void ABasePlayer::InputAxisMoveForward(float AxisValue)
{
	/*FRotator ReturnValue = GetControlRotation();
	float yaw = ReturnValue.Yaw;
	FRotator Rotator = FRotator(0.0f, yaw, 0.0f);
	FVector WorldDirection = Rotator.Vector();
	AddMovementInput(WorldDirection, AxisValue);*/

	AddMovementInput(FRotator(0.0f, GetControlRotation().Yaw, 0.0f).Vector(), AxisValue);
}
