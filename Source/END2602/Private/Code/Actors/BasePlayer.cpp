// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../END2602.h"

// Ctor that sets default values for ABasePlayer.
ABasePlayer::ABasePlayer() : SpringArmRelativeLocation(FVector(0.0, 80.0, 90.0)), TargetArmLength(205.f),
HUDClass(UPlayerHUD::StaticClass())
{
	// Tick already disabled

	// Initialization
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("springArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("cam");

	// Spring Arm Setup
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeLocation(SpringArmRelativeLocation);
	SpringArm->TargetArmLength = TargetArmLength;

	// Camera Setup
	Camera->SetupAttachment(SpringArm);

	TeamID = 0;
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	// Casting to APlayerController to attach the UPlayerHUD and disable/enable input to ABasePlayer
	if (AGamePlayerController* CastedController = Cast<AGamePlayerController>(GetController()))
	{
		PlayerController = CastedController;
		SetGenericTeamId(TeamID);
	}
	else
	{
		UE_LOG(BasePlayer, Error, TEXT("PlayerController is not AGamePlayerController or no controller present!"));
		Destroy();
	}

	// Casting to UPlayerHUD to show the PlayerHUD on screen.
	if (UPlayerHUD* CastedHUD = CreateWidget<UPlayerHUD>(PlayerController, HUDClass, ""))
	{
		HUDObject = CastedHUD; 

		// Allows the HUDObject to be displayed onto the screen
		HUDObject->AddToViewport();

		BaseRifle->OnAmmoChanged.AddDynamic(HUDObject, &UPlayerHUD::SetAmmo);                                           // Updates the CurrentAmmo and MaxAmmo values from the HUD

		if (HealthComponent)
		{
			HealthComponent->OnHurtDelegate.AddDynamic(HUDObject, &UPlayerHUD::SetHealth);                              // Updates the HealthBar from the HUD.
			HealthComponent->OnHealDelegate.AddDynamic(HUDObject, &UPlayerHUD::SetHealth);                              // Updates the HealthBar from the HUD.
			HealthComponent->OnMuerteDelegate.AddDynamic(HUDObject, &UPlayerHUD::SetHealth);                            // Updates the HealthBar from the HUD.

			AnimInstance->OnDeathEnded.AddDynamic(this, &ABasePlayer::PlayerLost);
		}
	}
	else
	{
		UE_LOG(BasePlayer, Error, TEXT("Failed to cast to a UPlayerHUD! (wrong HUDClass?)"));
	}
}

// Allows ABasePlayer to move left or right; strafing.
void ABasePlayer::InputAxisStrafe(float AxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::Y), AxisValue);
}

// Allows ABasePlayer to move forwards and backwards.
void ABasePlayer::InputAxisMoveForward(float AxisValue)
{
	AddMovementInput(FRotator(0.f, GetControlRotation().Yaw, 0.f).Vector(), AxisValue);
}

// Fires ABasePlayer's rifle.
void ABasePlayer::Fire()
{
	FRotator Direction = GetBaseAimRotation();
	BaseRifle->Fire(&Direction);
}

// Broadcasts ABasePlayer's OnPlayerLost delegate and disables the HUD after losing.
void ABasePlayer::PlayerLost()
{
	OnPlayerLost.Broadcast(); 

	// Disables the HUD and shows the cursor
	PlayerController->bShowMouseCursor = true;
	HUDObject->RemoveFromParent();
}

// Broadcasts ABasePlayer's OnPlayerLost delegate and disables the HUD after winning.
void ABasePlayer::PlayerWon()
{
	// Disables the HUD and player input
	DisableInput(PlayerController);
	HUDObject->RemoveFromParent();
}

// Called to bind functionality to input.
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Camera Binding
	PlayerInputComponent->BindAxis("TurnRight", this, &ABasePlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABasePlayer::AddControllerPitchInput);

	// Movement Binding
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::InputAxisMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::InputAxisStrafe);

	// Attack Binding
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ABasePlayer::Fire);

	// Reload Binding
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &ABasePlayer::Reload);
}

// Rotation matrix to rotate the projectile from the rifle to the PlayerHUD's Crosshair.
FRotator ABasePlayer::GetBaseAimRotation() const
{
	return FRotationMatrix::MakeFromX(HUDObject->GetDestination() - BaseRifle->GetSource()).Rotator();
}

// Decides whether or not ABasePlayer is allowed to use the health pickup.
bool ABasePlayer::CanPickupHealth() const
{
	return true;
}

// Decides whether or not ABasePlayer is allowed to use the max ammo pickup.
bool ABasePlayer::CanPickupMaxAmmo() const
{
	return true;
}