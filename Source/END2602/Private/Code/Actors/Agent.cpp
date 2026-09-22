// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Agent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"

 // Ctor that sets default values for AAgent.
AAgent::AAgent() : TintName("Tint"), Color(FLinearColor(0.0, 0.083584, 1.0, 0.0)), HealthRatioKey("HealthRatio"),
MaxAmmoKey("MaxAmmo"), CurrentAmmoKey("CurrentAmmo"), ActionStoppedMessage("ActionFinished") {} // Tick already disabled

// Called after loading the level and starting the game; runs before BeginPlay.
void AAgent::PostLoad()
{
	Super::PostLoad();
	GetMesh()->SetVectorParameterValueOnMaterials(TintName, FVector(Color));
}

// Called when the game starts or when spawned.
void AAgent::BeginPlay()
{
	Super::BeginPlay();

	UpdateBlackboardHealth(1.f);

	BaseRifle->OnActionStopped.AddDynamic(this, &AAgent::HandleActionFinished);
	BaseRifle->OnAmmoChanged.AddDynamic(this, &AAgent::UpdateBlackboardAmmo);

	AnimInstance->OnDeathEnded.AddDynamic(this, &AActor::K2_DestroyActor);
	GetMesh()->SetVectorParameterValueOnMaterials(TintName, FVector(Color));
}

// Updates the Health value in the AI Blackboard.
void AAgent::UpdateBlackboardHealth(float Ratio)
{
	if (APawn* AgentPawn = Cast<APawn>(this))
	{
		if (AAIController* AIController = Cast<AAIController>(AgentPawn->GetController()))
		{
			// Set the correct value for the health value in the AI Blackboard in the AIController
			AIController->GetBlackboardComponent()->SetValueAsFloat(HealthRatioKey, Ratio);
		}
	}
}

// Updates the Ammo values in the AI Blackboard.
void AAgent::UpdateBlackboardAmmo(float Current, float Max)
{
	if (APawn* AgentPawn = Cast<APawn>(this))
	{
		if (AAIController* AIController = Cast<AAIController>(AgentPawn->GetController()))
		{
			// Set the correct value for the current and max ammo values in the AI Blackboard in the AIController
			AIController->GetBlackboardComponent()->SetValueAsFloat(MaxAmmoKey, Max);
			AIController->GetBlackboardComponent()->SetValueAsFloat(CurrentAmmoKey, Current);
		}
	}
}

// Triggers the hit animation for the AAgent and updates the Health in the AI Blackboard.
void AAgent::HandleHurt(float Ratio)
{
	Super::HandleHurt(Ratio);
	UpdateBlackboardHealth(Ratio);
}

// Triggers the death animation for the AAgent.
void AAgent::HandleMuerte(float Ratio)
{
	Super::HandleMuerte(Ratio);

	// Prevents the AAgent from doing anything after death
	DetachFromControllerPendingDestroy();
}

// Sends a message to the UBTTaskNode to indicate the completion of a certain behavior.
void AAgent::HandleActionFinished()
{
	FAIMessage::Send(this, FAIMessage(ActionStoppedMessage, this, true));
}

// Allows the enemy to fire ABaseRifle.
void AAgent::EnemyAttack()
{
	BaseRifle->Fire();
}

// Allows the enemy to request a reload to the ABaseRifle's ammo.
void AAgent::EnemyReload()
{
	BaseRifle->RequestReload();
}