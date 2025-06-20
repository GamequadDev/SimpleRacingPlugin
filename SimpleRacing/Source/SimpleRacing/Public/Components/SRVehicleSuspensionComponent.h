// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "SRVehicleSuspensionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLERACING_API USRVehicleSuspensionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	
	USRVehicleSuspensionComponent();

protected:
	
	UPROPERTY()
	float LastHitDistance = 0;

	UPROPERTY(EditDefaultsOnly, Category=Suspension)
	UStaticMeshComponent* VehicleMainBody = nullptr;
	
public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditDefaultsOnly, Category=Suspension)
	float LenghtSuspension = 60.f;

	UPROPERTY(EditDefaultsOnly, Category=Suspension)
	float SpringForce = 2500000.0;

	UPROPERTY(EditDefaultsOnly, Category=Suspension)
	float SpringDumbing = 1000;
	
	UFUNCTION()
	void SetVehicleMainBody(UStaticMeshComponent* Vehicle);
};
