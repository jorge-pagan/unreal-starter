// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMenuPlayerController();

protected:
	UPROPERTY(EditDefaultsOnly) TSubclassOf<UUserWidget> MenuClass;
	UPROPERTY(EditDefaultsOnly) EMouseLockMode MouseLockType = EMouseLockMode::LockAlways;

	virtual void BeginPlay() override;
};
