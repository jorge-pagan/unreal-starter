// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Widgets/ResultsHUD.h"
#include "../END2602.h"

void UResultsHUD::LoadMainMenu()
{
	// Hack that does the travel logic for us to enter the main menu
	MainMenuButton->OnBackgroundButtonClicked.Broadcast();
}

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
	ResultsSwitch->SetActiveWidgetIndex(WinResultsSwitchIndex);
	ButtonBox->SetVisibility(ButtonVisibilityOnWin);

	FTimerHandle WinDisplayDurationTimer;
	GetWorld()->GetTimerManager().SetTimer(WinDisplayDurationTimer, this, 
		                                   &UResultsHUD::LoadMainMenu, WinMenuDisplayDuration);
}