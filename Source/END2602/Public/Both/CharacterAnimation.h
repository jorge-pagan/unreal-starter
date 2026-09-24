// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimInstance.h"

#include "CharacterAnimation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimationEvent);

/**
 *
 */
UCLASS()
class END2602_API UCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()

private:
	UCharacterAnimation();

	inline void MuerteEnded() { OnDeathEnded.Broadcast(); }

protected:
	UPROPERTY(EditDefaultsOnly, Category = Default) bool DebugFire = false;
	UPROPERTY(EditDefaultsOnly, Category = Default) bool DebugHit = false;
	UPROPERTY(EditDefaultsOnly, Category = Default) bool DebugMuerte = false;
	UPROPERTY(EditDefaultsOnly, Category = Default) bool DebugReload = false;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName ActionSlotName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) float Speed = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) float Direction = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) UAnimSequence* FireAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) UAnimSequence* HitAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) UAnimSequence* CurrentMuerteAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) TArray<UAnimSequence*> MuerteAssets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) UAnimSequence* ReloadAsset;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Default) FOnAnimationEvent OnReloadNow;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Default) FOnAnimationEvent OnReloadEnded;
	
	// Removes the Agent after death animation ends
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Default) FOnAnimationEvent OnDeathEnded;

	virtual void NativeBeginPlay() override;

	void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	void PreviewWindowUpdate();

	UFUNCTION(BlueprintCallable) void FireAnimation();
	UFUNCTION(BlueprintCallable) void HitAnimation();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) void MuerteAnimation(float Percent = 0.f);
	UFUNCTION(BlueprintCallable) void ReloadAnimation();
};