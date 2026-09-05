// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Controllers/AgentController.h"

void AAgentController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(BTAsset);
}