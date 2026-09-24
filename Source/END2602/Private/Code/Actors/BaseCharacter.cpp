// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseCharacter.h"
#include "../END2602.h"

// Ctor that sets default values for ABaseCharacter.
ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WeaponClass(ABaseRifle::StaticClass()), WeaponSocketName(TEXT("WeaponSocket"))
{
	// Disables ticking
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	// Sets position of the character mesh
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -90.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	// BaseRifle component creation
	BaseRifleChildComponent = CreateDefaultSubobject<UChildActorComponent>("BaseRifleChildComponent");
	BaseRifleChildComponent->SetChildActorClass(WeaponClass);
	// Attaching to the mesh component
	BaseRifleChildComponent->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, 
		                                       WeaponSocketName);

	// Health cmponent creation
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

// Called when the game starts or when spawned.
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Setting Child Class
	BaseRifleChildComponent->bEditableWhenInherited = true;
	BaseRifleChildComponent->SetChildActorClass(WeaponClass);

	// Casting to ABaseRifle to be able to fire
	if (ABaseRifle* CastedRifle = BaseRifle ? BaseRifle : Cast<ABaseRifle>(BaseRifleChildComponent->GetChildActor()))
	{
		BaseRifle = CastedRifle;
	}
	else
	{
		UE_LOG(BaseCharacter, Error, TEXT("Failed to convert Rifle to \"ABaseRifle!\""));
		return;
	}

	// Casting to UCharacterAnimation to use its functions and set its delegates
	if (UCharacterAnimation* CastedAnimInstance = Cast<UCharacterAnimation>(GetMesh()->GetAnimInstance()))
	{
		AnimInstance = CastedAnimInstance;
		BaseRifle->OnRifleFireDelegate.AddDynamic(AnimInstance, &UCharacterAnimation::FireAnimation);                   // Plays the FireAnimation when the rifle is fired.
		BaseRifle->OnReloadStart.AddDynamic(AnimInstance, &UCharacterAnimation::ReloadAnimation);                       // Plays the ReloadAnimation when the reload key is pressed.
		AnimInstance->OnReloadNow.AddDynamic(BaseRifle, &ABaseRifle::ReloadAmmo);                                       // Refills the CurrentAmmo and broadcasts ABaseRifle's OnAmmoChanged delegate.
		AnimInstance->OnReloadEnded.AddDynamic(BaseRifle, &ABaseRifle::ActionStopped);                                  // Allows the rifle to fire again and broadcasts ABaseRifle's OnActionStopped delegate.
	}
	else
	{
		UE_LOG(BaseCharacter, Error, TEXT("Failed to convert AnimInstance to \"UCharacterAnimation!\""));
		return;
	}

	// Sets the HealthComponent delegates
	if (HealthComponent)
	{
		HealthComponent->OnHurtDelegate.AddDynamic(this, &ABaseCharacter::HandleHurt);
		HealthComponent->OnMuerteDelegate.AddDynamic(this, &ABaseCharacter::HandleMuerte);
	}
	else
	{
		UE_LOG(BaseCharacter, Error, TEXT("No HealthComponent is present in ABaseCharacter!"));
	}
}

// Triggers the hit animation for the ABaseCharacter.
void ABaseCharacter::HandleHurt(float NotUsed)
{
	AnimInstance->HitAnimation();
}

// Triggers the death animation and disables input for the ABaseCharacter.
void ABaseCharacter::HandleMuerte(float NotUsed)
{
	AnimInstance->MuerteAnimation();
	SetActorEnableCollision(true);

	// Disables movement input
	DisableInput(nullptr);

	// Disables ABaseRifle
	BaseRifle->OwnerMuerto();
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


// Decides whether or not ABaseCharacter is allowed to use the health pickup.
bool ABaseCharacter::CanPickupHealth() const
{
	return false;
}