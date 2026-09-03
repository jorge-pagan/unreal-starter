// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

#include "PlayerHUD.generated.h"

/**
 *
 */
UCLASS()
class END2602_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Remember to set the BP_CodePlayer's HUDObject to the WBP in the editor (and not the UPlayerHUD class)

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) class UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) UImage* Crosshair;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) UMaterialInstanceDynamic* DynamicMaterial;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) FVector EndPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) FName ColorName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) FLinearColor SafeColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) FLinearColor DangerColor;

	FCollisionObjectQueryParams ObjectTypes;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	virtual bool Initialize() override;
	virtual void PostLoad() override;

	UFUNCTION(BlueprintCallable)
	FVector GetDestination() const { return EndPoint; };

	UFUNCTION(BlueprintCallable)
	void SetHealth(float Percent);
};
