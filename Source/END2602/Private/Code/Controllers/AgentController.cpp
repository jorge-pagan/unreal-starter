// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Controllers/AgentController.h"

// I understand the downsides of hardcoding a value to a variable, but in these instances, I wanted to set a
// default value to the variable while still retaining the editable benefits from the editor
// (unless I'm wrong and that's not how the UE editor works). I only did it so I won't have to set the variables
// again if I do end up porting the code to another project like we did at the start of class.
// 
// I hope you understand!

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