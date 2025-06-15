// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Vehicles/Pawns/SRCarPawn.h"
#include "Track/SRTrackPath.h"
#include "SRCarAIController.generated.h"

UCLASS()
class SIMPLERACING_API ASRCarAIController : public AAIController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	ASRCarPawn* OwnerCar;

	UPROPERTY()
	ASRTrackPath* TrackPathActor;
};
