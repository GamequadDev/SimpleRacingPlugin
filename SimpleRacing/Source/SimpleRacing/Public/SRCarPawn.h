// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SRVehicleSuspensionComponent.h"
#include "Vehicles/Pawns/SRVehiclePawn.h"
#include "SRCarPawn.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLERACING_API ASRCarPawn : public ASRVehiclePawn
{
	GENERATED_BODY()

public:
	ASRCarPawn();
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Suspension, meta=(AllowPrivateAccess = "true"))
	USRVehicleSuspensionComponent* FrontLeftSuspensionComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Suspension, meta=(AllowPrivateAccess = "true"))
	USRVehicleSuspensionComponent* FrontRightSuspensionComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Suspension, meta=(AllowPrivateAccess = "true"))
	USRVehicleSuspensionComponent* RearLeftSuspensionComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Suspension, meta=(AllowPrivateAccess = "true"))
	USRVehicleSuspensionComponent* RearRightSuspensionComp;



public:

	virtual void Tick(float DeltaTime) override;
	
	virtual void SteerRight(float Value) override;
	virtual void MoveForward(float Value) override;
	
	

	
};
