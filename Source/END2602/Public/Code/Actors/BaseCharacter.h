// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Both/CharacterAnimation.h"
#include "GameFramework/Character.h"
#include "Both/HealthComponent.h"
#include "Code/Actors/BaseRifle.h"
#include "../END2602.h"

#include "BaseCharacter.generated.h"

UCLASS(Abstract)
class END2602_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Default) UChildActorComponent* BaseRifleChildComponent;
	UPROPERTY(EditDefaultsOnly, Category = Default) ABaseRifle* BaseRifle;
	UPROPERTY(EditDefaultsOnly, Category = Default) TSubclassOf<AActor> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = Default) FName WeaponSocketName;

	UPROPERTY(EditDefaultsOnly, Category = Default) UCharacterAnimation* AnimInstance;
	UPROPERTY(EditDefaultsOnly, Category = Default) UStaticMesh* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, Category = Default) UHealthComponent* HealthComponent;

	UFUNCTION(BlueprintCallable)
	virtual void HandleHurt(float NotUsed);

	UFUNCTION(BlueprintCallable)
	virtual void HandleMuerte(float NotUsed);

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
