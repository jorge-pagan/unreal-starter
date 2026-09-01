// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../END2602.h"

// Sets default values
AProjectile::AProjectile() : Size(1.0f, 1.0f,1.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollision);
	SphereCollision->SetWorldScale3D(Size);

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");
	SphereMesh->SetCollisionProfileName("NoCollision");
	SphereMesh-> SetRelativeScale3D(FVector(0.6f,0.6f,0.6f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	SphereMesh->SetStaticMesh(Asset.Object);
	SphereMesh->SetupAttachment(SphereCollision);

	SphereCollision->OnComponentHit.AddDynamic(this, &AProjectile::HandleHit);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 1900;
	ProjectileMovement->MaxSpeed = 1900;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(Game, Warning, TEXT("Hit was Called"));
	UE_LOG(Game, Warning, TEXT("Other Actor Name is: %s"), *OtherActor->GetName());
	Destroy();
}

