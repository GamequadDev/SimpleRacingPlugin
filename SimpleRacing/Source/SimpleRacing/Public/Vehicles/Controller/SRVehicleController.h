// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SRVehicleController.generated.h"

class ASRVehiclePawn;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


/*
UINTERFACE(MinimalAPI, Blueprintable)
class UVehicleControllerInterface : public UInterface
{
	GENERATED_BODY()
};

class IVehicleControllerInterface
{
	GENERATED_BODY()

	public:

	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);
};*/

UCLASS()
class SIMPLERACING_API ASRVehicleController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveXAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveYAction;

protected:

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;
	
	void HandleMoveXAction(const FInputActionValue& Value);
	void HandleMoveYAction(const FInputActionValue& Value);

	
	ASRVehiclePawn* PawnVehicle = nullptr;
	
	
};
