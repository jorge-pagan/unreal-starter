// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BasePickup.generated.h"

UCLASS(Abstract)
class END2602_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

protected:
	UPROPERTY(EditDefaultsOnly) UBoxComponent* BoxCollision;

	virtual void PostLoad() override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult);
	virtual void PostPickup();

private:
	UFUNCTION() void BoundOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		                          bool bFromSweep, const FHitResult& SweepResult);
};
