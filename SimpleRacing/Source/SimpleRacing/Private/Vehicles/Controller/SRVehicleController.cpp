// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#include "Vehicles/Pawns/SRVehiclePawn.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Vehicles/Controller/SRVehicleController.h"



void ASRVehicleController::BeginPlay()
{

	Super::BeginPlay();

	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	} 

	
	APawn* ControlledPawn = GetPawn();
	if(ControlledPawn)
	{
		ASRVehiclePawn* PlayerPawn = Cast<ASRVehiclePawn>(ControlledPawn);
		if(PlayerPawn)
		{
			PawnVehicle = PlayerPawn;
		}
	}
}

void ASRVehicleController::SetupInputComponent()
{

	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveYAction, ETriggerEvent::Triggered,this,&ASRVehicleController::HandleMoveYAction);
		EnhancedInputComponent->BindAction(MoveXAction, ETriggerEvent::Triggered,this,&ASRVehicleController::HandleMoveXAction);
		
	}
	else
	{
	//	UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ASRVehicleController::HandleMoveYAction(const FInputActionValue& Value)
{
	
	float InputValue = Value.Get<float>();
	if(PawnVehicle)
	{
		PawnVehicle->MoveForward(InputValue);
	}
	
}


void ASRVehicleController::HandleMoveXAction(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	if (PawnVehicle)
	{
		PawnVehicle->SteerRight(InputValue);
	}

}
