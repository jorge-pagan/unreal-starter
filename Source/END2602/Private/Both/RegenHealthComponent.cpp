// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/RegenHealthComponent.h"
#include "../END2602.h"

URegenHealthComponent::URegenHealthComponent()
{
	MaxHealth = 11.f;

	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void URegenHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(Game, Warning, TEXT("BeginPlay"));

	OnMuerteDelegate.AddDynamic(this, &URegenHealthComponent::HandleDeath);
}

void URegenHealthComponent::TurnTickOff()
{
	UE_LOG(Game, Warning, TEXT("TurnTickOff"));
	PrimaryComponentTick.SetTickFunctionEnable(false);
	
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(RegenTimerHandle);
	}
}

void URegenHealthComponent::TurnTickOn()
{
	UE_LOG(Game, Warning, TEXT("TurnTickOn"));
	PrimaryComponentTick.SetTickFunctionEnable(true);
}

void URegenHealthComponent::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::HandleDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	if (Damage > 0 && IsAlive())
	{
		UE_LOG(Game, Warning, TEXT("Healing timer enabled"));
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().SetTimer(RegenTimerHandle, this, &URegenHealthComponent::TurnTickOn, 2.0f);
		}
	}
}

void URegenHealthComponent::HandleDeath(float Value)
{
	TurnTickOff();
	UE_LOG(Game, Warning, TEXT("I died"));
}

void URegenHealthComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UE_LOG(Game, Warning, TEXT("I am ticking"));

	HandleDamage(GetOwner(), -1.0f * DeltaTime, nullptr, nullptr, GetOwner());

	if (IsFullHealth()) TurnTickOff();
}
