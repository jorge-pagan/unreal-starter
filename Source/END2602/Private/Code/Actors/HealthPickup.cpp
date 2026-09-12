// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/HealthPickup.h"
#include "Engine/DamageEvents.h"

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