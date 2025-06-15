// Copyright 2025 Mateusz Wozniak. All Rights Reserved.


#include "Track/SRTrackPath.h"
#include "Kismet/GameplayStatics.h"

ASRTrackPath::ASRTrackPath()
{
	PrimaryActorTick.bCanEverTick = false;

	TrackPath = CreateDefaultSubobject<USplineComponent>(TEXT("Path"));
	TrackPath->SetupAttachment(RootComponent);
	TrackPath->SetClosedLoop(true);
}

void ASRTrackPath::BeginPlay()
{
	Super::BeginPlay();

	if(TrackPath)
	{
		int MaxPoints = TrackPath->GetNumberOfSplinePoints();

		for (int i = 0; i<MaxPoints;i++)
		{
			ASRTrackCheckpoint* SpawnedPoint = SpawnCheckPoint(MaxPoints - i,i);
			SpawnedPoint->MaxNumberCheckpoint = MaxPoints - 1;
			SpawnedPoint->NumberCheckpoint = MaxPoints - i;
		}
	}
}

ASRTrackCheckpoint* ASRTrackPath::SpawnCheckPoint(int Number,int Index)
{

	FSplinePoint Point = TrackPath->GetSplinePointAt(Index, ESplineCoordinateSpace::World);
	float Lenght = TrackPath->GetDistanceAlongSplineAtSplinePoint(Index);
	
	FVector SpawnLocation = TrackPath->GetLocationAtDistanceAlongSpline(Lenght, ESplineCoordinateSpace::World);
	FRotator SpawnRotation = Point.Rotation;
	
	ASRTrackCheckpoint* SpawnedPoint = GetWorld()->SpawnActor<ASRTrackCheckpoint>(
		ASRTrackCheckpoint::StaticClass(),
		SpawnLocation,
		SpawnRotation
	);
	return SpawnedPoint;
}

