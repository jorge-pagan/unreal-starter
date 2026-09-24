// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeHealth, float, Percent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class END2602_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Default) float CurrentHealth = 0.f;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION() virtual void HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		                          class AController* InstigatedBy, AActor* DamageCauser);

	FORCEINLINE bool IsFullHealth() const { return CurrentHealth / MaxHealth == 1.f; }
	FORCEINLINE bool IsAlive() const { return CurrentHealth > 0; }
public:
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnywhere, Category = Default) float MaxHealth = 5.f;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Variable) FOnChangeHealth OnHurtDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Variable) FOnChangeHealth OnHealDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Variable) FOnChangeHealth OnMuerteDelegate;
};
