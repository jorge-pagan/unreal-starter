// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Widgets/MainMenuHUD.h"
#include "Code/Instances/CodeGameInstance.h"
#include "../END2602.h"

void UMainMenuHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (UCodeGameInstance* GI = Cast<UCodeGameInstance>(GetGameInstance()))
	{
		PlayButton->OnBackgroundButtonClicked.AddDynamic(GI, &UCodeGameInstance::LoadFirstLevel);
		QuitButton->OnBackgroundButtonClicked.AddDynamic(GI, &UCodeGameInstance::QuitTheGame);
	}
	else UE_LOG(Game, Warning, TEXT("Failed to cast the GameInstance because of an incorrect socketed GameInstance!"));
}