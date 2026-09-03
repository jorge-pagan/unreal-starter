// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter() : WeaponClass(ABaseRifle::StaticClass()), WeaponSocketName(TEXT("WeaponSocket"))
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -90.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	BaseRifleChildComponent = CreateDefaultSubobject<UChildActorComponent>("BaseRifleChildComponent");

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Setting Child Class
	BaseRifleChildComponent->bEditableWhenInherited = true;
	BaseRifleChildComponent->SetChildActorClass(WeaponClass);

	// Attaching to the Mesh Component
	BaseRifleChildComponent->AttachToComponent(GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketName);

	// Casting to ABaseRifle to be able to fire
	if (ABaseRifle* CastedRifle = Cast<ABaseRifle>(BaseRifleChildComponent->GetChildActor()))
	{
		BaseRifle = CastedRifle;
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("Failed to convert Rifle to \"ABaseRifle\""));
		return;
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

