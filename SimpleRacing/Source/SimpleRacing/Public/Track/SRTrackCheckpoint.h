// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "SRTrackCheckpoint.generated.h"

UCLASS()
class SIMPLERACING_API ASRTrackCheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASRTrackCheckpoint();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Track, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* Checkpoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Track, meta=(AllowPrivateAccess = "true"))
	int NumberCheckpoint  = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Track, meta=(AllowPrivateAccess = "true"))
	int MaxNumberCheckpoint = -1;
	
	UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
