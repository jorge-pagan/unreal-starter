// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/ButtonWithText.h"

void UButtonWithText::HandleClickButton()
{
	OnBackgroundButtonClicked.Broadcast();
}

void UButtonWithText::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Information) Information->SetText(Info);
}

void UButtonWithText::NativeConstruct()
{
	BackgroundButton->OnClicked.AddDynamic(this, &UButtonWithText::HandleClickButton);
}