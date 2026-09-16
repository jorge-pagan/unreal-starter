// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/HealthPickup.h"
#include "Code/Interfaces/PickupQueriesInterface.h"
#include "../END2602.h"

AHealthPickup::AHealthPickup()
{
	DamageAmount = -1.6f;
	BoxCollision->SetRelativeScale3D(FVector(1.5f, 1.5f, 2.f));

	ParticleSystem->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
	ParticleSystem->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.7f));
}

void AHealthPickup::PostPickup()
{
	ABasePickup::PostPickup();
}

bool AHealthPickup::CanPickup(AActor* OtherActor) const
{
	if (IPickupQueriesInterface* I = Cast<IPickupQueriesInterface>(OtherActor))
	{
		return I->CanPickupHealth();
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("Overlapped actor from AHealthPickup does not have an IPickupQueriesInterface"));
	}

	return false;
}