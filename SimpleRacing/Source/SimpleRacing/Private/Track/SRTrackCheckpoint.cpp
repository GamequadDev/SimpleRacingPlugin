// Copyright 2025 Mateusz Wozniak. All Rights Reserved.


#include "Track/SRTrackCheckpoint.h"
#include "Vehicles/Pawns/SRVehiclePawn.h"

ASRTrackCheckpoint::ASRTrackCheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;

	Checkpoint = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Checkpoint->SetupAttachment(RootComponent);

	FVector BoxScale = FVector(20,1000,400);
	Checkpoint->SetBoxExtent(BoxScale,true);
	
	Checkpoint->OnComponentBeginOverlap.AddDynamic(this, &ASRTrackCheckpoint::OnOverlap);
}

void ASRTrackCheckpoint::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ASRVehiclePawn* Vehicle = Cast<ASRVehiclePawn>(OtherActor);
	if(Vehicle)
	{
		if(Vehicle->CurrentPoint == MaxNumberCheckpoint)
		{
			Vehicle->CurrentPoint = 0;
			return;
		}
		
		if(Vehicle->CurrentPoint == 0)
		{
			Vehicle->StartRacingTimer();
			Vehicle->CurrentPoint +=1;
			return;
		}
		
		if(Vehicle->CurrentPoint == NumberCheckpoint)
		{
			Vehicle->CurrentPoint +=1;
		}
	}
}