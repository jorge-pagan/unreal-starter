// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Agent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"

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

	if (AgentPawn)
	{
		AAIController* AIController = Cast<AAIController>(AgentPawn->GetController());

		if (AIController) AIController->GetBlackboardComponent()->SetValueAsFloat(HealthRatioKey, Ratio);
	}
}

void AAgent::UpdateBlackboardAmmo(float Current, float Max)
{
	APawn* AgentPawn = Cast<APawn>(this);

	if (AgentPawn)
	{
		AAIController* AIController = Cast<AAIController>(AgentPawn->GetController());

		if (AIController) AIController->GetBlackboardComponent()->SetValueAsFloat(AmmoKey, Current);
	}
}

void AAgent::BeginPlay()
{
	Super::BeginPlay();

	UpdateBlackboardHealth(1.f);

	BaseRifle->OnActionStopped.AddDynamic(this, &AAgent::HandleActionFinished);
	BaseRifle->OnAmmoChanged.AddDynamic(this, &AAgent::UpdateBlackboardAmmo);
}

void AAgent::HandleHurt(float Ratio)
{
	Super::HandleHurt(Ratio);
	UpdateBlackboardHealth(Ratio);
}

void AAgent::HandleMuerte(float Ratio)
{
	Super::HandleMuerte(Ratio);
	DetachFromControllerPendingDestroy();
}

void AAgent::HandleActionFinished()
{
	FAIMessage::Send(this, FAIMessage(ActionStoppedMessage, this, true));
}

void AAgent::EnemyReload()
{
	BaseRifle->RequestReload();
}

void AAgent::EnemyAttack()
{
	BaseRifle->Fire();
}