// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Agent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

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

void AAgent::UpdateBlackboardHealth(float Ratio)
{
	APawn* AgentPawn = Cast<APawn>(this);
	Cast<AAIController>(AgentPawn->GetController())->GetBlackboardComponent()->SetValueAsFloat(HealthRatioKey, Ratio);
}

void AAgent::BeginPlay()
{
	Super::BeginPlay();

	UpdateBlackboardHealth(1.f);
}

void AAgent::HandleHurt(float Ratio)
{
	Super::HandleHurt(Ratio);
	UpdateBlackboardHealth(Ratio);
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