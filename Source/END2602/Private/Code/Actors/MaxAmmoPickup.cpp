// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/MaxAmmoPickup.h"
#include "../END2602.h"


AMaxAmmoPickup::AMaxAmmoPickup()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	FAttachmentTransformRules TRules = { EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false };
	Mesh->AttachToComponent(BoxCollision, TRules);
	Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void AMaxAmmoPickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{
	if (IPickupQueriesInterface* I = Cast<IPickupQueriesInterface>(OtherActor))
	{
		I->IncreaseMaxAmmo(IncreaseAmount);
	}
}

bool AMaxAmmoPickup::CanPickup(AActor* OtherActor) const
{
	if (IPickupQueriesInterface* I = Cast<IPickupQueriesInterface>(OtherActor))
	{
		return I->CanPickupMaxAmmo();
	}
	else
	{
		UE_LOG(MaxAmmoPickup, Error, TEXT("Overlapped actor from AMaxAmmoPickup does not have an IPickupQueriesInterface!"));
	}

	return false;
}