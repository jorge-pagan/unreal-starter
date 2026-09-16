// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../END2602.h"

ABasePlayer::ABasePlayer() : SpringArmRelativeLocation(FVector(0.0, 80.0, 90.0)), TargetArmLength(205.f),
HUDClass(UPlayerHUD::StaticClass())
{
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
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = nullptr;

	if (APlayerController* CastedController = Cast<APlayerController>(GetController()))
		PlayerController = CastedController;
	else
	{
		UE_LOG(Game, Warning, TEXT("No PlayerController present in ABasePlayer!"));
		Destroy();
	}

	if (UPlayerHUD* CastedHUD = CreateWidget<UPlayerHUD>(PlayerController, HUDClass, ""))
	{
		HUDObject = CastedHUD;

		HUDObject->AddToViewport();

		BaseRifle->OnAmmoChanged.AddDynamic(HUDObject, &UPlayerHUD::SetAmmo);

		if (HealthComponent)
		{
			HealthComponent->OnHurtDelegate.AddDynamic(HUDObject, &UPlayerHUD::SetHealth);
			HealthComponent->OnHealDelegate.AddDynamic(HUDObject, &UPlayerHUD::SetHealth);
			HealthComponent->OnMuerteDelegate.AddDynamic(HUDObject, &UPlayerHUD::SetHealth);
		}
	}
}

void ABasePlayer::InputAxisMoveForward(float AxisValue)
{

	//FRotator return_val = GetControlRotation();
	//float yaw = return_val.Yaw;

	//FRotator make_rotator(0.f, yaw, 0.f);
	//FVector world_dir = make_rotator.Vector();

	// Same as above
	// FRotator(0.f, GetControlRotation().Yaw, 0.f).Vector()

	AddMovementInput(FRotator(0.f, GetControlRotation().Yaw, 0.f).Vector(), AxisValue);
}

void ABasePlayer::InputAxisStrafe(float AxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::Y), AxisValue);
}

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

FRotator ABasePlayer::GetBaseAimRotation() const
{
	return FRotationMatrix::MakeFromX(HUDObject->GetDestination() - BaseRifle->GetSource()).Rotator();
}

void ABasePlayer::Fire()
{
	FRotator Direction = GetBaseAimRotation();
	BaseRifle->Fire(&Direction);
}

void ABasePlayer::Reload()
{
	BaseRifle->RequestReload();
}

bool ABasePlayer::CanPickupHealth() const
{
	return true;
}