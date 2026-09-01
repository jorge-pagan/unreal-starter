// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CharacterAnimation.h"
#include "KismetAnimationLibrary.h"

void UCharacterAnimation::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();

	if (Pawn)
	{
		//isValid
		Velocity = Pawn->GetVelocity().Length();
	}
	else
	{
		//notValid

		//Preview Window
		PreviewWindowUpdate();
	}
}

void UCharacterAnimation::PreviewWindowUpdate_Implementation()
{

}
