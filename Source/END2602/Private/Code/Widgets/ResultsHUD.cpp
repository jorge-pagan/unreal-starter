// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Widgets/ResultsHUD.h"
#include "../END2602.h"

void UResultsHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (UCodeGameInstance* GI = Cast<UCodeGameInstance>(GetGameInstance()))
	{
		GameInstance = GI;

		PlayAgainButton->OnBackgroundButtonClicked.AddDynamic(GameInstance, &UCodeGameInstance::ReloadLevel);
		MainMenuButton->OnBackgroundButtonClicked.AddDynamic(GameInstance, &UCodeGameInstance::QuitToMenu);
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("Failed to retrieve game instance or not using the correct game instance!"));
	}
}

void UResultsHUD::WinConditionMet()
{
	ResultsSwitch->ActiveWidgetIndex = WinWidgetSwitcherIndex;
	ButtonBox->SetVisibility(ButtonVisibilityOnWin);
}