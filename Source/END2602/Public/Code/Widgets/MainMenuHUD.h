// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Both/ButtonWithText.h"

#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API UMainMenuHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION() inline void LoadFirstGame_Wrapper() { GameInstance->LoadFirstLevel(); }
	UFUNCTION() inline void QuitTheGame_Wrapper() { GameInstance->QuitTheGame(); }
	
protected:
	// Remember to set the BP_CodeMenuPlayerController's MenuObject to the WBP in the editor (and not UMainMenuHUD)
	
	UCodeGameInstance* GameInstance;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) UButtonWithText* PlayButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) UButtonWithText* QuitButton;

	virtual void NativeConstruct() override;
};
