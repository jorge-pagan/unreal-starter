// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimation.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API UCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds)override;

	UFUNCTION(BlueprintNativeEvent)
	void PreviewWindowUpdate();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
	float Velocity;
};
