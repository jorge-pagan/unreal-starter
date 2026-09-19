// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/ButtonWithText.h"
#include "../END2602.h"

void UButtonWithText::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Information) Information->SetText(Info);
	else UE_LOG(ButtonWithText, Error, TEXT("Information text block not bound to the widget!"));
}

void UButtonWithText::NativeConstruct()
{
	if (!BackgroundButton) UE_LOG(ButtonWithText, Error, TEXT("BackgroundButton not bound to the widget!"));

	BackgroundButton->OnClicked.AddDynamic(this, &UButtonWithText::HandleClickButton);
}

void UButtonWithText::HandleClickButton()
{
	OnBackgroundButtonClicked.Broadcast();
}