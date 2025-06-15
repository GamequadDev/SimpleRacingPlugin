// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SRVehicleSuspensionComponent.h"
#include "Vehicles/Pawns/SRVehiclePawn.h"
#include "SRCarPawn.generated.h"

UCLASS()
class SIMPLERACING_API ASRCarPawn : public ASRVehiclePawn
{
	GENERATED_BODY()

public:
	ASRCarPawn();
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Suspension, meta=(AllowPrivateAccess = "true"))
	USRVehicleSuspensionComponent* SuspensionFrontLeftComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Suspension, meta=(AllowPrivateAccess = "true"))
	USRVehicleSuspensionComponent* SuspensionFrontRightComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Suspension, meta=(AllowPrivateAccess = "true"))
	USRVehicleSuspensionComponent* SuspensionRearLeftComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Suspension, meta=(AllowPrivateAccess = "true"))
	USRVehicleSuspensionComponent* SuspensionRearRightComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Wheel, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelFrontLeftMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Wheel, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelFrontRightMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Wheel, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelRearLeftMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Wheel, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelRearRightMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Wheel, meta=(AllowPrivateAccess = "true"))
	USceneComponent* SceneWheelForwardRightComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Wheel, meta=(AllowPrivateAccess = "true"))
	USceneComponent* SceneWheelForwardLeftComponent;
	
	UPROPERTY()
	float TargetSteerAngle = 0;
	
	UPROPERTY()
	float CurrentSteerAngle = 0;
	
	UPROPERTY()
	float ForwardAxisValue = 0;
	
public:

	virtual void Tick(float DeltaTime) override;
	
	virtual void SteerRight(float Value) override;
	virtual void MoveForward(float Value) override;
	
	void UpdateVehicleForce(float Value);
};
