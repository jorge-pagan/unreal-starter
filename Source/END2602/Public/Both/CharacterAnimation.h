// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../END2602.h"

#include "CharacterAnimation.generated.h"

/**
 *
 */
UCLASS()
class END2602_API UCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()

private:
	UCharacterAnimation();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default) float Speed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default) float Direction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) bool DebugFire;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) bool DebugHit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default) bool DebugMuerte;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default) UAnimSequence* FireAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default) UAnimSequence* HitAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default) UAnimSequence* CurrentMuerteAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default) TArray<UAnimSequence*> MuerteAssets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default) FName ActionSlotName;

public:
	void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	void PreviewWindowUpdate();

	UFUNCTION(BlueprintCallable)
	void FireAnimation();

	UFUNCTION(BlueprintCallable)
	void HitAnimation();

	UFUNCTION(BlueprintCallable)
	void MuerteAnimation(float Percent = 0.f);
};
