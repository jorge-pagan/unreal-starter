// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BaseRifle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRifleFireDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChanged, float, Current, float, Max);

UCLASS()
class END2602_API ABaseRifle : public AActor
{
	GENERATED_BODY()

public:
	
	ABaseRifle();

	UPROPERTY(BlueprintAssignable, BlueprintCallable) FRifleFireDelegate OnRifleFireDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnAmmoChanged OnAmmoChanged;
	UPROPERTY(EditDefaultsOnly, Category = Default) float MaxAmmo;

protected:
	// Don't forget to set the BaseCharacter's WeaponClass object to BP_CodeBaseRifle in the editor 
	// (and not the ABaseRifle class)

	UPROPERTY(VisibleAnywhere, Category = Default) USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(VisibleAnywhere, Category = Default) APawn* Parent;

	UPROPERTY(EditDefaultsOnly, Category = Default) TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName ProjectileSpawnSocketName;
	UPROPERTY(EditDefaultsOnly, Category = Default) float FireDelay;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	inline void UseAmmo() { CurrentAmmo -= 1.f; OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo); }

private:
	UPROPERTY(VisibleAnywhere, Category = Default) float CurrentAmmo;

	bool Alive = true;

	bool ActionHappening = false;

	inline bool CanShoot() const { return !ActionHappening && Alive && CurrentAmmo > 0.f; }

	void ActionStopped();

public:
	FVector GetSource();

	inline void OwnerMuerto() { Alive = false; }

	inline void ReloadAmmo() { CurrentAmmo = MaxAmmo; OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo); }

	void Fire(const FRotator* Direction = nullptr);

};
