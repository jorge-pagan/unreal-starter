// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseCharacter.h"
#include "../END2602.h"

// Sets default values
ABaseCharacter::ABaseCharacter() : WeaponClass(ABaseRifle::StaticClass()), WeaponSocketName(TEXT("WeaponSocket"))
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -90.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	BaseRifleChildComponent = CreateDefaultSubobject<UChildActorComponent>("BaseRifleChildComponent");
	BaseRifleChildComponent->SetChildActorClass(WeaponClass);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Setting Child Class
	BaseRifleChildComponent->bEditableWhenInherited = true;
	BaseRifleChildComponent->SetChildActorClass(WeaponClass);

	// Attaching to the Mesh Component
	BaseRifleChildComponent->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, 
		                                       WeaponSocketName);

	// Casting to ABaseRifle to be able to fire
	if (ABaseRifle* CastedRifle = BaseRifle ? BaseRifle : Cast<ABaseRifle>(BaseRifleChildComponent->GetChildActor()))
	{
		BaseRifle = CastedRifle;
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("Failed to convert Rifle to \"ABaseRifle\""));
		return;
	}

	// Casting AnimInstance to UCharacterAnimation
	if (UCharacterAnimation* CastedAnimInstance = Cast<UCharacterAnimation>(GetMesh()->GetAnimInstance()))
	{
		AnimInstance = CastedAnimInstance;
		BaseRifle->OnRifleFireDelegate.AddDynamic(AnimInstance, &UCharacterAnimation::FireAnimation);
		BaseRifle->OnReloadStart.AddDynamic(AnimInstance, &UCharacterAnimation::ReloadAnimation);
		AnimInstance->OnReloadNow.AddDynamic(BaseRifle, &ABaseRifle::ReloadAmmo);
		AnimInstance->OnReloadEnded.AddDynamic(BaseRifle, &ABaseRifle::ActionStopped);
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("Failed to convert AnimInstance to \"UCharacterAnimation\""));
		return;
	}

	if (HealthComponent)
	{
		HealthComponent->OnHurtDelegate.AddDynamic(this, &ABaseCharacter::HandleHurt);
		HealthComponent->OnMuerteDelegate.AddDynamic(this, &ABaseCharacter::HandleMuerte);
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("No HealthComponent is present in ABaseCharacter!"));
	}
}

void ABaseCharacter::HandleHurt(float NotUsed)
{
	AnimInstance->HitAnimation();
}

void ABaseCharacter::HandleMuerte(float NotUsed)
{
	AnimInstance->MuerteAnimation();

	SetActorEnableCollision(true);
	DisableInput(nullptr);
	BaseRifle->OwnerMuerto();
}

bool ABaseCharacter::CanPickupHealth() const
{
	return false;
}