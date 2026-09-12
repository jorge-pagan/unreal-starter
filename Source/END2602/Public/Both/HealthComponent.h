// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHurtDelegate, float, Percent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealDelegate, float, Percent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMuerteDelegate, float, Percent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class END2602_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Default) float CurrentHealth;

	UFUNCTION() void HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		                          class AController* InstigatedBy, AActor* DamageCauser);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnywhere, Category = Default) float MaxHealth;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Variable) FOnHurtDelegate OnHurtDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Variable) FOnHealDelegate OnHealDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Variable) FOnMuerteDelegate OnMuerteDelegate;
};
