// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "../END2602.h"

void UPlayerHUD::PostLoad()
{
	Super::PostLoad();

	EndPoint = FVector::Zero();
	ColorName = TEXT("Color");
	SafeColor = FLinearColor(0.f, 0.35f, 1.f, 1.f);
	DangerColor = FLinearColor(0.85f, 0.1f, 0.1f, 1.f);

	ObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	ObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
}

bool UPlayerHUD::Initialize()
{
	bool r = Super::Initialize();
	if (!HealthBar) UE_LOG(PlayerHUD, Error, TEXT("HealthBar not bound to widget!"));

	if (Crosshair)
	{
		DynamicMaterial = Crosshair->GetDynamicMaterial();
	}
	else
	{
		DynamicMaterial = nullptr;
		UE_LOG(PlayerHUD, Error, TEXT("Crosshair not bound to widget!"));
	}

	if (!CurrentAmmo || !MaxAmmo) UE_LOG(PlayerHUD, Error, TEXT("CurrentAmmo and/or MaxAmmo not bound to widget!"));

	return r;
}

void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Variable Declaration
	FMatrix ViewMatrix;
	FHitResult HitResult;
	ULocalPlayer* LocalPlayer = GetOwningPlayer()->GetLocalPlayer();
	UPrimitiveComponent* HitComponent;
	FSceneViewProjectionData Projection;
	ECollisionChannel CollisionObjectType;
	TArray<AActor*, FDefaultAllocator> IgnoredActors;
	FGeometry CachedGeometry = Crosshair->GetCachedGeometry();
	FVector2D LocalCoordinate(0.f, 0.f), PixelPosition, ViewportPosition, ScreenPosition;
	FVector WorldPosition, WorldDirection, Start;


	// Translating local coordiantes of the cached geometry to local viewport coordinates
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), CachedGeometry,
		LocalCoordinate, PixelPosition, ViewportPosition);


	// Calculating the screen's position
	ScreenPosition = PixelPosition + (CachedGeometry.GetAbsoluteSize() * 0.5f);

	// Retreiving Projection
	LocalPlayer->GetProjectionData(LocalPlayer->ViewportClient->Viewport, Projection);

	// Building the View Matrix
	ViewMatrix = Projection.ComputeViewProjectionMatrix().InverseFast();

	// Transforming 2D screen space to world space (3D)
	FSceneView::DeprojectScreenToWorld(ScreenPosition, Projection.GetConstrainedViewRect(),
		ViewMatrix, WorldPosition, WorldDirection);


	// Creating the line from Start to EndPoint
	Start = WorldPosition + WorldDirection;
	EndPoint = Start + (WorldDirection * 100000.f);

	// Adding object types that can be hit in the collision trace

	// Ignoring the player itself
	IgnoredActors.Add(GetOwningPlayer());

	// Collision trace along the given line from to return the first hit encountered
	GetWorld()->LineTraceSingleByObjectType(HitResult, Start, EndPoint, ObjectTypes);

	// Extracting HitResult data
	HitComponent = HitResult.GetComponent();

	// Checking the type of collision object from the hit component
	CollisionObjectType = HitComponent ? HitComponent->GetCollisionObjectType() : ECC_GameTraceChannel18;
	                                                                 // This game trace channel is treated as a 'none'.

	if (CollisionObjectType == ECC_Pawn)
	{
		// Hittable object present in the crosshair, Danger Color
		EndPoint = HitResult.Location;
		DynamicMaterial->SetVectorParameterValue(ColorName, DangerColor);
	}
	else if (CollisionObjectType == ECC_WorldDynamic)
	{
		// Hittable object present in the crosshair, Safe Color
		EndPoint = HitResult.Location;
		DynamicMaterial->SetVectorParameterValue(ColorName, SafeColor);
	}
	
	else
	{
		// No hittable objects present in the crosshair, Safe Color
		DynamicMaterial->SetVectorParameterValue(ColorName, SafeColor);
	}
}

void UPlayerHUD::SetHealth(float Percent)
{
	HealthBar->SetPercent(Percent);
}

void UPlayerHUD::SetAmmo(float Current, float Max)
{
	CurrentAmmo->SetText(FText::AsNumber(Current));
	MaxAmmo->SetText(FText::AsNumber(Max));
}