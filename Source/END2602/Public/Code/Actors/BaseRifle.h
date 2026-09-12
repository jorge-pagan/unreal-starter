// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseRifle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionStopped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRifleFireDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChanged, float, Current, float, Max);

UCLASS()
class END2602_API ABaseRifle : public AActor
{
	GENERATED_BODY()

private:
	float CurrentAmmo;
	bool Alive = true;
	bool ActionHappening = false;

	inline bool CanShoot() const { return !ActionHappening && Alive && CurrentAmmo > 0.f; }

protected:
	// Don't forget to set the BaseCharacter's WeaponClass object to BP_CodeBaseRifle in the editor 
	// (and not this ABaseRifle class)

	UPROPERTY(VisibleAnywhere, Category = Default) APawn* Parent;
	UPROPERTY(VisibleAnywhere, Category = Default) USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, Category = Default) float FireDelay;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName ProjectileSpawnSocketName;
	UPROPERTY(EditDefaultsOnly, Category = Default) TSubclassOf<AActor> ProjectileClass;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	inline void UseAmmo() { CurrentAmmo -= 1.f; OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo); }

public:
	ABaseRifle();

	UPROPERTY(EditDefaultsOnly, Category = Default) float MaxAmmo;
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnReloadStart OnReloadStart;
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnActionStopped OnActionStopped;
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FRifleFireDelegate OnRifleFireDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnAmmoChanged OnAmmoChanged;

	FVector GetSource();

	inline void OwnerMuerto() { Alive = false; }

	UFUNCTION()	void ReloadAmmo();
	void RequestReload();

	void Fire(const FRotator* Direction = nullptr);
	UFUNCTION() void ActionStopped();
};
