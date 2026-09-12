// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CharacterAnimation.h"
#include "KismetAnimationLibrary.h"
#include "../END2602.h"

UCharacterAnimation::UCharacterAnimation() : DebugFire(false), DebugHit(false), DebugMuerte(false),
CurrentMuerteAsset(nullptr), ActionSlotName("Action")
{

}

void UCharacterAnimation::PreviewWindowUpdate()
{
	if (DebugMuerte)
	{
		MuerteAnimation();
		DebugMuerte = false;
	}
	else if (DebugHit)
	{
		HitAnimation();
		DebugHit = false;
	}
	else if (DebugFire)
	{
		FireAnimation();
		DebugFire = false;
	}
	else if (DebugReload)
	{
		ReloadAnimation();
		DebugReload = false;
	}
}

void UCharacterAnimation::FireAnimation()
{
	PlaySlotAnimationAsDynamicMontage(FireAsset, ActionSlotName);
}

void UCharacterAnimation::HitAnimation()
{
	PlaySlotAnimationAsDynamicMontage(HitAsset, ActionSlotName);
}

void UCharacterAnimation::MuerteAnimation(float Percent)
{
	// The modulo sign prevents Rand from going above Array.Num() - 1!
	CurrentMuerteAsset = MuerteAssets[FMath::Rand() % MuerteAssets.Num()];
}

void UCharacterAnimation::ReloadAnimation()
{
	PlaySlotAnimationAsDynamicMontage(ReloadAsset, ActionSlotName);
}

void UCharacterAnimation::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (APawn* pawn = TryGetPawnOwner())
	{
		FVector vel = pawn->GetVelocity();

		Speed = vel.Size();
		Direction = UKismetAnimationLibrary::CalculateDirection(vel, pawn->GetActorRotation());
	}
	else // UE Editor APB Preview Only
	{
		PreviewWindowUpdate();
	}
}

void UCharacterAnimation::HandleReloadNow()
{
	OnReloadNow.Broadcast();
}

void UCharacterAnimation::HandleReloadEnded()
{
	OnReloadEnded.Broadcast();
}