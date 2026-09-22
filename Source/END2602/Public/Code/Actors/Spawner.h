// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Code/GameModes/CodeGameMode.h"
#include "Both/HealthComponent.h"
#include "Components/CapsuleComponent.h"

#include "Spawner.generated.h"

UCLASS()
class END2602_API ASpawner : public AActor
{
	GENERATED_BODY()
	
private:	
	FTimerHandle TimerHandle;
	IWinConditionInterface* CachedGameMode;

protected:
	UPROPERTY(EditDefaultsOnly) float SpawnDelay = 20.f;
	UPROPERTY(EditDefaultsOnly) float SpawnRadius = 5.f;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<AActor> SpawnClass;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<AActor> GameModeClass;
	UPROPERTY(EditDefaultsOnly) UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditDefaultsOnly) UHealthComponent* HealthComponent;
	UPROPERTY(EditDefaultsOnly) UStaticMeshComponent* Mesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Spawn();
	UFUNCTION() virtual void HandleMuerte(float Percent);

public:	
	ASpawner();
};
