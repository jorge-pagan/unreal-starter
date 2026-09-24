// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Spawner.generated.h"

UCLASS()
class END2602_API ASpawner : public AActor
{
	GENERATED_BODY()
	
private:	
	FTimerHandle TimerHandle;
	class IWinConditionInterface* CachedGameMode;

protected:
	UPROPERTY(EditDefaultsOnly) float SpawnDelay = 20.f;
	UPROPERTY(EditDefaultsOnly) float SpawnRadius = 5.f;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<AActor> SpawnClass;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<AActor> GameModeClass;
	UPROPERTY(EditDefaultsOnly) class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditDefaultsOnly) class UHealthComponent* HealthComponent;
	UPROPERTY(EditDefaultsOnly) class UStaticMeshComponent* Mesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Spawn();
	UFUNCTION() virtual void HandleMuerte(float Percent);

public:	
	ASpawner();
};
