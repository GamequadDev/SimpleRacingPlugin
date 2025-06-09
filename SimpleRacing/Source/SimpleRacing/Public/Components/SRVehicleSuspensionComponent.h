// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SRVehicleSuspensionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLERACING_API USRVehicleSuspensionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USRVehicleSuspensionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY()
	float LastHitDistance = 0;

	UPROPERTY(EditDefaultsOnly, Category=Suspension)
	UStaticMeshComponent* VehicleMainBody = nullptr;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
	
	UPROPERTY(EditDefaultsOnly, Category=Debug)
	bool bDebugMode = false;

	UPROPERTY(EditDefaultsOnly, Category=Suspension)
	float LenghtSuspension = 60.f;

	UPROPERTY(EditDefaultsOnly, Category=Suspension)
	float SpringForce = 2500000.0;

	UPROPERTY(EditDefaultsOnly, Category=Suspension)
	float SpringDumbing = 1000;


	UFUNCTION()
	void SetVehicleMainBody(UStaticMeshComponent* Vehicle);
	
};
