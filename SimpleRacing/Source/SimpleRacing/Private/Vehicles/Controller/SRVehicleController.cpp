// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#include "Vehicles/Controller/SRVehicleController.h"

#include "Vehicles/Pawns/SRVehiclePawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"

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
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveYAction, ETriggerEvent::Triggered,this,&ASRVehicleController::HandleMoveYAction);
		EnhancedInputComponent->BindAction(MoveXAction, ETriggerEvent::Triggered,this,&ASRVehicleController::HandleMoveXAction);
		EnhancedInputComponent->BindAction(ChangeCameraAction, ETriggerEvent::Started,this,&ASRVehicleController::HandleChangeCameraAction);
		EnhancedInputComponent->BindAction(MoveYAction, ETriggerEvent::Completed,this,&ASRVehicleController::HandleMoveYAction);
		EnhancedInputComponent->BindAction(CameraXAction, ETriggerEvent::Triggered,this,&ASRVehicleController::HandleCameraXAction);
	}
}

void ASRVehicleController::HandleMoveYAction(const FInputActionValue& Value)
{
	
	float InputValue = Value.Get<float>();
	if (PawnVehicle)
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

void ASRVehicleController::HandleCameraXAction(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	if (PawnVehicle)
	{
		PawnVehicle->CameraRotationX(InputValue);
	}
}

void ASRVehicleController::HandleChangeCameraAction()
{
	if (PawnVehicle)
	{
		PawnVehicle->ChangeCamera();
	}
}