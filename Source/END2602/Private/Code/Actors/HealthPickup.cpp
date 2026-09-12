// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/HealthPickup.h"
#include "Code/Interfaces/PickupQueriesInterface.h"
#include "Engine/DamageEvents.h"
#include "Code/Actors/BasePlayer.h"
#include "EngineUtils.h"

AHealthPickup::AHealthPickup()
{
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
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;

		if (IPickupQueriesInterface* I = Cast<IPickupQueriesInterface>(Actor))
		{
			ABasePlayer* P = Cast<ABasePlayer>(I);
			return P ? P->CanPickupHealth() : I->CanPickupHealth();
		}
	}

	return false;
}