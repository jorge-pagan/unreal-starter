// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "ButtonWithText.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);

/**
 * 
 */
UCLASS()
class END2602_API UButtonWithText : public UUserWidget
{
	GENERATED_BODY()

private:
	UFUNCTION() void HandleClickButton();
	
protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget)) UButton* BackgroundButton;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget)) UTextBlock* Information;

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, Category = Default) FText Info;
	UPROPERTY(EditDefaultsOnly, BlueprintAssignable) FOnButtonClicked OnBackgroundButtonClicked;
};
