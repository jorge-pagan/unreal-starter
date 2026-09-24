// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Agent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"
#include "../END2602.h"

 // Ctor that sets default values for AAgent.
AAgent::AAgent() : TintName("Tint"), Color(FLinearColor(0.0, 0.083584, 1.0, 0.0)), HealthRatioKey("HealthRatio"),
MaxAmmoKey("MaxAmmo"), CurrentAmmoKey("CurrentAmmo"), ActionStoppedMessage("ActionFinished") 
{
	// Tick already disabled

	TeamID = 1;
}

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

	BaseRifle->OnActionStopped.AddDynamic(this, &AAgent::HandleActionFinished);
	BaseRifle->OnAmmoChanged.AddDynamic(this, &AAgent::UpdateBlackboardAmmo);

	AnimInstance->OnDeathEnded.AddDynamic(this, &AActor::K2_DestroyActor);
	GetMesh()->SetVectorParameterValueOnMaterials(TintName, FVector(Color));
	
	if (APawn* AgentPawn = Cast<APawn>(this))
	{
		if (AAgentController* AGC = Cast<AAgentController>(AgentPawn->GetController()))
		{
			AgentController = AGC;
			SetGenericTeamId(TeamID);
		}
		else UE_LOG(Agent, Error, TEXT("AIController is not AAgentController or no AIController present!"));
	}
	else UE_LOG(Agent, Error, TEXT("AAgent is not a Pawn!"));

	UpdateBlackboardHealth(1.f);
}

// Updates the Health value in the AI Blackboard.
void AAgent::UpdateBlackboardHealth(float Ratio)
{
	// Set the correct value for the health value in the AI Blackboard in the AIController
	AgentController->GetBlackboardComponent()->SetValueAsFloat(HealthRatioKey, Ratio);
}

// Updates the Ammo values in the AI Blackboard.
void AAgent::UpdateBlackboardAmmo(float Current, float Max)
{	
	// Set the correct value for the current and max ammo values in the AI Blackboard in the AIController
	AgentController->GetBlackboardComponent()->SetValueAsFloat(MaxAmmoKey, Max);
	AgentController->GetBlackboardComponent()->SetValueAsFloat(CurrentAmmoKey, Current);
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

void AAgent::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	Super::SetGenericTeamId(NewTeamID);
	AgentController->SetGenericTeamId(NewTeamID);
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