// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Agent.h"

AAgent::AAgent() : TintName("Tint"), Color(FLinearColor(0.0, 0.083584, 1.0, 0.0))
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = true;
}

void AAgent::PostLoad()
{
	Super::PostLoad();
	GetMesh()->SetVectorParameterValueOnMaterials(TintName, FVector(Color));
}

void AAgent::HandleActionFinished()
{
	FAIMessage::Send(this, FAIMessage(ActionStoppedMessage, this, true));
}

void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAgent::EnemyAttack()
{
	BaseRifle->Fire();
}