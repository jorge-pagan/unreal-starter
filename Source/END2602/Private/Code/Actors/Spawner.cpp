// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Spawner.h"
#include "Code/Actors/Agent.h"
#include "EngineUtils.h"

// Sets default values
ASpawner::ASpawner() : SpawnClass(AAgent::StaticClass()), GameModeClass(ACodeGameMode::StaticClass())
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->GetBodyInstance()->SetObjectType(ECollisionChannel::ECC_Pawn);

	FAttachmentTransformRules TRules = { EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false };
	Mesh->AttachToComponent(CapsuleComponent, TRules);
	Mesh->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComponent->OnMuerteDelegate.AddDynamic(this, &ASpawner::HandleMuerte);

	if (UWorld* World = GetWorld())
	{
		for (TActorIterator<AActor> It(World); It; ++It)
		{
			if (IWinConditionInterface* I = Cast<IWinConditionInterface>(*It))
			{
				CachedGameMode = I;
				CachedGameMode->AddEnemy(this);
			}
		}
	}
	else
	{
		UE_LOG(Spawner, Error, TEXT("Failed to retrieve World!"));
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpawner::Spawn, SpawnDelay);
}

void ASpawner::Spawn()
{
	FTransform SpawnTransform;
	
	SpawnTransform.SetLocation(GetActorLocation());
	SpawnTransform.SetRotation(GetActorRotation().Quaternion());

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = nullptr;
	SpawnParams.Instigator = nullptr;

	AActor* Spawned = GetWorld()->SpawnActor(SpawnClass, &SpawnTransform, SpawnParams);

	Spawned->AddActorLocalOffset(FVector(SpawnRadius, 0.f, 0.f));

	if (CachedGameMode) CachedGameMode->AddEnemy(Spawned);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpawner::Spawn, SpawnDelay);
}

void ASpawner::HandleMuerte(float Percent)
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	Destroy();
}