// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AnimNotify/ReloadNow.h"
#include "Code/Interfaces/HandleReloadInterface.h"
#include "UObject/UObjectIterator.h" 

void UReloadNow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	for (TObjectIterator<UObject> It; It; ++It)
	{
		UObject* Actor = *It;

		if (IHandleReloadInterface* I = Cast<IHandleReloadInterface>(Actor))
		{
			I->HandleReloadNow();
		}
	}
}