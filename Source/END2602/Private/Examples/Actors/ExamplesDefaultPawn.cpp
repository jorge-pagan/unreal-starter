// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/Actors/ExamplesDefaultPawn.h"
#include "../END2602.h"
#include "GameFramework/PlayerInput.h"
#include "EngineUtils.h" // TActorIterator (GetActorOfClass in Blueprints)
#include "Examples/Actors/ExampleInterfaceTwo.h"

// Sets default values
AExamplesDefaultPawn::AExamplesDefaultPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExamplesDefaultPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//Up Cast
	AActor* Actor = this;

	//down Cast
	APawn* Pawn = Cast<APawn>(Actor);

	if (!Pawn)
	{
		UE_LOG(Game, Warning, TEXT("Actor is %s"), *Pawn->GetName());
	}
	else
	{
		UE_LOG(Game, Log, TEXT("Numbers are %d or %f"), 4, 7.1f);
	}
	UE_LOG(Game, Error, TEXT("Velocity is %s"), *GetVelocity().ToString());

	UE_LOG(Game, Error, TEXT("It is %s"), true ? TEXT("True") : TEXT("False"));

	for (TActorIterator<AExampleActorWithInterfaces> It(GetWorld()); It; ++It)
	{
		Actor = *It;
		// Don't use UInterface of object for this

		// Use the I version of the interface for attaching to simple functions

		if (IExampleInterfaceOne* I = Cast<IExampleInterfaceOne>(Actor)) // This work because the interface is attached in C++
		{
			UE_LOG(Game, Warning, TEXT("I was able to cast the ExampleActorWithInterfaces to our first interface type"));
			I->TestFunction(); // Equivalent to the EnemyAttack interface that should be implemented in C++
		}

		// This will not work because the interface is attached in blueprints
		if (IExampleInterfaceTwo* I2 = Cast<IExampleInterfaceTwo>(Actor))
		{
			UE_LOG(Game, Warning, TEXT("I was able to cast the ExampleActorWithInterfaces to our second interface type"));
			I2->BlueprintImplementableEvent_Sept(); // Equivalent to the EnemyAttack interface that should be implemented in C++
		}

		// If the interafce is attached in Blueprints, use the Implements functions to check instead
		if (Actor->Implements<UExampleInterfaceTwo>())
		{
			UE_LOG(Game, Warning, TEXT("Actor implements our second interface type"));

			IExampleInterfaceTwo::Execute_BlueprintImplementableEvent_Sept(Actor);
		}

		if (IExampleInterfaceThree* I3 = Cast<IExampleInterfaceThree>(Actor))
		{
			// Do not call the interface function directly on the object 
			// it will crash and tell you to call the execute version of the function instead
			//I3->BlueprintNativeEvent_Sept();
			//I3->Execute_BlueprintNativeEvent_Sept(Actor); // This will work
			//IExampleInterfaceThree::Execute_BlueprintNativeEvent_Sept(Actor); // This is prefered
		}
	}
}

// Called every frame
void AExamplesDefaultPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AExamplesDefaultPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Test_Spawn", EKeys::SpaceBar));

	PlayerInputComponent->BindAction("Test_Spawn", EInputEvent::IE_Pressed, this, &AExamplesDefaultPawn::Spawn);
}

void AExamplesDefaultPawn::Spawn()
{
	FActorSpawnParameters Params;
	Params.Instigator = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	GetWorld()->SpawnActor<AActor>(SpawnBlueprintClass, GetActorTransform(), Params);
}

