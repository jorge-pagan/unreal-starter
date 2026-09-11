// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseRifle.h"
#include "Code/Actors/Projectile.h" // Used only to define ProjectileClass in code, otherwise it had to be defined in editor
#include "Code/Actors/Agent.h"
#include "EngineUtils.h"
#include "../END2602.h"

// Sets default values
ABaseRifle::ABaseRifle() : ProjectileClass(AProjectile::StaticClass()), ProjectileSpawnSocketName("MuzzleFlashSocket"),
FireDelay(0.7f)
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
		UE_LOG(Game, Warning, TEXT("Failed to convert parent actor to pawn. Need a pawn to own this rifle."));
		Destroy();
	}
}

void ABaseRifle::ActionStopped()
{
	ActionHappening = false;

	OnActionStopped.Broadcast();
}

FVector ABaseRifle::GetSource()
{
	return SkeletalMesh->GetSocketLocation(ProjectileSpawnSocketName);
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
		UE_LOG(Game, Log, TEXT("Projectile Fired"));
	}
}
