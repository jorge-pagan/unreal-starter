// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseRifle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRifleEvent);
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

	UPROPERTY(EditDefaultsOnly, Category = Default) float MaxAmmo;
	UPROPERTY(EditDefaultsOnly, Category = Default) float FireDelay;
	UPROPERTY(VisibleAnywhere, Category = Default) APawn* Parent;
	UPROPERTY(VisibleAnywhere, Category = Default) USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditDefaultsOnly, Category = Default) FName ProjectileSpawnSocketName;
	UPROPERTY(EditDefaultsOnly, Category = Default) TSubclassOf<AActor> ProjectileClass;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UseAmmo();

public:
	ABaseRifle();

	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnRifleEvent OnReloadStart;
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnRifleEvent OnActionStopped;
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnRifleEvent OnRifleFireDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnAmmoChanged OnAmmoChanged;

	FVector GetSource();

	inline void OwnerMuerto() { Alive = false; }

	UFUNCTION()	void ReloadAmmo();
	void RequestReload();

	void Fire(const FRotator* Direction = nullptr);
	UFUNCTION() void ActionStopped();
};
