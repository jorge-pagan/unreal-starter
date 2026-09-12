// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/DamagePickup.h"
#include "Engine/DamageEvents.h"

ADamagePickup::ADamagePickup() : DamageAmount(2.f)
{
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystem");
	
	BoxCollision->SetRelativeScale3D(FVector(1.6f, 1.6f, 1.6f));

	FAttachmentTransformRules TRules = { EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false };
	ParticleSystem->AttachToComponent(BoxCollision, TRules);

	ParticleSystem->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
	ParticleSystem->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.25f));
}

void ADamagePickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{
	Super::HandlePickup(OtherActor, SweepResult);

	TSubclassOf<UDamageType> const DamageType = UDamageType::StaticClass();
	FDamageEvent DamageEvent(DamageType);

	OtherActor->TakeDamage(DamageAmount, DamageEvent, NULL, this);
}