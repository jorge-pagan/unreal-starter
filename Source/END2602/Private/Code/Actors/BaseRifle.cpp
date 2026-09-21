// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseRifle.h"
#include "Code/Actors/Projectile.h" // Used only to define ProjectileClass in code, otherwise it had to be defined in editor
#include "../END2602.h"

// Sets default values
ABaseRifle::ABaseRifle() : ProjectileClass(AProjectile::StaticClass()), ProjectileSpawnSocketName("MuzzleFlashSocket")
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	// Initialization
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
}

// Called when the game starts or when spawned
void ABaseRifle::BeginPlay()
{
	Super::BeginPlay();

	if (APawn* CastedParent = Cast<APawn>(AActor::GetParentActor()))
	{
		Parent = CastedParent;
	}
	else
	{
		UE_LOG(BaseRifle, Error, TEXT("Failed to convert parent actor to pawn! Need a pawn to own this rifle!"));
		Destroy();
	}

	// Delays the call to ReloadAmmo to bind the delegates to the 
	// PlayerHUD Ammo Update and Agent's Update Blackboard Ammo functions
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ABaseRifle::ReloadAmmo);
}

void ABaseRifle::UseAmmo()
{
	CurrentAmmo = FMath::Max(0, CurrentAmmo - 1.f);
	OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
}

void ABaseRifle::ActionStopped()
{
	ActionHappening = false;

	OnActionStopped.Broadcast();
}

void ABaseRifle::ReloadAmmo()
{
	CurrentAmmo = MaxAmmo;
	OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
}

void ABaseRifle::RequestReload()
{
	if (!ActionHappening)
	{
		ActionHappening = true;

		// Triggers the animation which eventually changes the data
		OnReloadStart.Broadcast();
	}
}

void ABaseRifle::Fire(const FRotator* Direction)
{
	if (CanShoot())
	{
		ActionHappening = true;

		FTimerHandle RifleResetTime;
		GetWorld()->GetTimerManager().SetTimer(RifleResetTime, this, &ABaseRifle::ActionStopped, FireDelay);

		FTransform ActorTransform;
		ActorTransform.SetLocation(GetSource());
		ActorTransform.SetRotation(Direction ? Direction->Quaternion() : Parent->GetBaseAimRotation().Quaternion());

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Parent->GetController();
		SpawnParams.Instigator = Parent;

		GetWorld()->SpawnActor(ProjectileClass, &ActorTransform, SpawnParams);

		UseAmmo();

		OnRifleFireDelegate.Broadcast();
	}
}

void ABaseRifle::IncreaseMaxAmmo(float Increment)
{
	MaxAmmo = FMath::Max(0, MaxAmmo + Increment);
	OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
}