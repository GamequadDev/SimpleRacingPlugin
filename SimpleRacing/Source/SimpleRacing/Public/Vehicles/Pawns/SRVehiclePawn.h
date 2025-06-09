// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SRVehiclePawn.generated.h"

UCLASS()
class SIMPLERACING_API ASRVehiclePawn : public APawn
{
	GENERATED_BODY()

public:
	
	ASRVehiclePawn();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Suspension, meta=(AllowPrivateAccess = "true"))
	USceneComponent* SceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Suspension, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* VehicleBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parameters)
	float VehicleAcceleration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Parameters, meta = (AllowPrivateAccess = "true"))
	float MaxSpeedKph = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters, meta = (AllowPrivateAccess = "true"))
	UCurveFloat* CurveAccelerationEngine;
	
	UFUNCTION()
	bool LineTraceParallelSurfaceVector(USceneComponent* Component, float HeightCar, FVector& VectorNormalize);
	
public:	

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void SteerRight(float Value){};
	
	UFUNCTION()
	virtual void MoveForward(float Value){};
	
	UFUNCTION()
	float GetSpeedKph();
};
