// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "../END2602.h"

// Sets default values
AProjectile::AProjectile() : ProjectileDespawnDelay(3.f), CollisionRelativeScale(FVector(0.18, 0.18, 0.18)),
SphereSize(FVector(0.6, 0.6, 0.6)), Damage(1.f)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	// Sphere Collision Setup
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollision);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::HandleOverlap);
	SphereCollision->SetRelativeScale3D(CollisionRelativeScale);


	// Sphere Mesh Setup
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");
	SphereMesh->SetCollisionProfileName("NoCollision");
	SphereMesh->SetupAttachment(SphereCollision);
	SphereMesh->SetRelativeScale3D(SphereSize);

	// Projectile Movement Setup
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->InitialSpeed = 1900.f;
	ProjectileMovement->MaxSpeed = 1900.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (AController* CastedController = Cast<AController>(GetOwner()))
		OwnerController = CastedController;
	else
		UE_LOG(Game, Warning, TEXT("Owner needs to be a controller"));

	FTimerHandle ProjectileTimer;
	GetWorld()->GetTimerManager().SetTimer(ProjectileTimer, this,
		&AProjectile::K2_DestroyActor, ProjectileDespawnDelay);
}

// Created a function with the overlap function signature
void AProjectile::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TSubclassOf<UDamageType> DamageSubclass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
	FDamageEvent DamageEvent(DamageSubclass);

	OtherActor->TakeDamage(Damage, DamageEvent, OwnerController, this);


	Destroy();
}