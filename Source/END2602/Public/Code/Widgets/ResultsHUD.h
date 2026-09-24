// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "ResultsHUD.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API UResultsHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	void LoadMainMenu();

protected:
	UPROPERTY(EditDefaultsOnly) float WinMenuDisplayDuration = 2.f;
	UPROPERTY(EditDefaultsOnly) ESlateVisibility ButtonVisibilityOnWin = ESlateVisibility::Hidden;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) class UWidgetSwitcher* ResultsSwitch;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) class UVerticalBox* ButtonBox;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) class UButtonWithText* PlayAgainButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) class UButtonWithText* MainMenuButton;

	virtual void NativeConstruct() override;

public:
	void WinConditionMet();
};
