// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Code/Instances/CodeGameInstance.h"
#include "Both/ButtonWithText.h"
#include "../END2602.h"

#include "ResultsHUD.generated.h"

/**
 * 
 */
UCLASS()
class END2602_API UResultsHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	UCodeGameInstance* GameInstance;

	void LoadMainMenu();

protected:
	UPROPERTY(EditDefaultsOnly) float WinMenuDisplayDuration = 2.f;
	UPROPERTY(EditDefaultsOnly) ESlateVisibility ButtonVisibilityOnWin = ESlateVisibility::Hidden;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) UWidgetSwitcher* ResultsSwitch;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) UVerticalBox* ButtonBox;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) UButtonWithText* PlayAgainButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) UButtonWithText* MainMenuButton;

	virtual void NativeConstruct() override;

public:
	void WinConditionMet();
};
