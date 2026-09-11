// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Code/Interfaces/HandleReloadInterface.h"
#include "../END2602.h"

#include "CharacterAnimation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadNow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadEnded);

/**
 *
 */
UCLASS()
class END2602_API UCharacterAnimation : public UAnimInstance, public IHandleReloadInterface
{
	GENERATED_BODY()

private:
	UCharacterAnimation();

protected:
	UPROPERTY(EditDefaultsOnly, Category = Default) bool DebugFire;
	UPROPERTY(EditDefaultsOnly, Category = Default) bool DebugHit;
	UPROPERTY(EditDefaultsOnly, Category = Default) bool DebugMuerte;
	UPROPERTY(EditDefaultsOnly, Category = Default) bool DebugReload;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName ActionSlotName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) float Speed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) float Direction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) UAnimSequence* FireAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) UAnimSequence* HitAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) UAnimSequence* CurrentMuerteAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) TArray<UAnimSequence*> MuerteAssets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) UAnimSequence* ReloadAsset;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Default) FOnReloadNow OnReloadNow;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Default) FOnReloadEnded OnReloadEnded;

	void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	void PreviewWindowUpdate();

	UFUNCTION(BlueprintCallable)
	void SetReloadAnimation(UAnimSequence* NewAsset) { ReloadAsset = NewAsset; }

	UFUNCTION(BlueprintCallable)
	void FireAnimation();

	UFUNCTION(BlueprintCallable)
	void HitAnimation();

	UFUNCTION(BlueprintCallable)
	void MuerteAnimation(float Percent = 0.f);

	UFUNCTION(BlueprintCallable)
	void ReloadAnimation();

	void HandleReloadNow() override;

	void HandleReloadEnded() override;
};