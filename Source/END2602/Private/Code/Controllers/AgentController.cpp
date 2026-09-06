// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Controllers/AgentController.h"

AAgentController::AAgentController() : PlayerKey("Player") // Default value given to the variable
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");
}

void AAgentController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AAgentController::HandlePerception);
	RunBehaviorTree(BTAsset);
}

void AAgentController::HandlePerception(AActor* ActorInView, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed()) Blackboard.Get()->SetValueAsObject(PlayerKey, ActorInView);
	else Blackboard.Get()->ClearValue(PlayerKey);
}