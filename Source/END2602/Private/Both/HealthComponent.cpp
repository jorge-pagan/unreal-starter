// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/HealthComponent.h"
#include "../END2602.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent() : MaxHealth(5.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  
	// You can turn these features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamage);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::HandleDamage(AActor* DamagedActor, float Damage,
	const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
	if (CurrentHealth > 0.f)
	{
		OnHurtDelegate.Broadcast(CurrentHealth / MaxHealth);
	}
	else
	{
		OnMuerteDelegate.Broadcast(0.f);
		GetOwner()->OnTakeAnyDamage.Clear();
	}

}