// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AnimNotify/ReloadNow.h"
#include "Both/CharacterAnimation.h"

void UReloadNow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (UCharacterAnimation* CA = Cast<UCharacterAnimation>(MeshComp->GetAnimInstance()))
	{
		CA->HandleReloadNow();
	}
}