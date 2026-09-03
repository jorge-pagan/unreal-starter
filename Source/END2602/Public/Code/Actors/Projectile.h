// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Projectile.generated.h"

UCLASS()
class END2602_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Don't forget to set the BP_BaseRifle's ProjectileClass object to BP_CodeProjectile in the editor
	// (and not the AProjectile class)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) class USphereComponent* SphereCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile) float ProjectileDespawnDelay;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FVector CollisionRelativeScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) class UStaticMeshComponent* SphereMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FVector SphereSize;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) class UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) float Damage;

private:
	AController* OwnerController;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
