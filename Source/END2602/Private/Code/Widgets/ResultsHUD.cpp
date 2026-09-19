// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Widgets/ResultsHUD.h"
#include "../END2602.h"

void UResultsHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (UCodeGameInstance* GI = Cast<UCodeGameInstance>(GetGameInstance()))
	{
		if (PlayAgainButton && MainMenuButton)
		{
			PlayAgainButton->OnBackgroundButtonClicked.AddDynamic(GI, &UCodeGameInstance::ReloadLevel);
			MainMenuButton->OnBackgroundButtonClicked.AddDynamic(GI, &UCodeGameInstance::QuitToMenu);
		}
		else UE_LOG(ResultsHUD, Error, TEXT("PlayAgainButton and/or MainMenuButton not bound to the widget!"));
	}
	else UE_LOG(ResultsHUD, Error, TEXT("Failed to retrieve game instance or not using the correct game instance!"));

	if (!ResultsSwitch) UE_LOG(ResultsHUD, Error, TEXT("ResultsSwitch not bound to the widget!"));
	if (!ButtonBox) UE_LOG(ResultsHUD, Error, TEXT("ButtonBox not bound to the widget!"));
}

void UResultsHUD::LoadMainMenu()
{
	// Hack that does the travel logic for us to enter the main menu
	MainMenuButton->OnBackgroundButtonClicked.Broadcast();
}

void UResultsHUD::WinConditionMet()
{
	ResultsSwitch->SetActiveWidgetIndex(1);
	ButtonBox->SetVisibility(ButtonVisibilityOnWin);

	FTimerHandle WinDisplayDurationTimer;
	GetWorld()->GetTimerManager().SetTimer(WinDisplayDurationTimer, this, 
		                                   &UResultsHUD::LoadMainMenu, WinMenuDisplayDuration);
}