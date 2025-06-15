// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Track/SRTrackCheckpoint.h"
#include "SRTrackPath.generated.h"

UCLASS()
class SIMPLERACING_API ASRTrackPath : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASRTrackPath();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Track, meta=(AllowPrivateAccess = "true"))
	USplineComponent* TrackPath;

	ASRTrackCheckpoint* SpawnCheckPoint(int Number,int Index);
};
