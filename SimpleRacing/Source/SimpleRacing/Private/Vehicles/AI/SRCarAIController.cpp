// Copyright 2025 Teyon. All Rights Reserved.


#include "Vehicles/AI/SRCarAIController.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

void ASRCarAIController::BeginPlay()
{
	Super::BeginPlay();

	OwnerCar = Cast<ASRCarPawn>(GetPawn());
	
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(),ASRTrackPath::StaticClass());
	if(FoundActor)
	{
		TrackPathActor = Cast<ASRTrackPath>(FoundActor);
	}
	
	
}

void ASRCarAIController::Tick(float DeltaTime)
{
	if(OwnerCar)
	{
		OwnerCar->MoveForward(0.9f);

		FVector LocationComponent = OwnerCar->GetVehicleBodyLocation();
		float Distance = TrackPathActor->TrackPath->GetDistanceAlongSplineAtLocation(LocationComponent,ESplineCoordinateSpace::World);
		Distance -= 800;
		FVector NewLocation = TrackPathActor->TrackPath->GetLocationAtDistanceAlongSpline(Distance,ESplineCoordinateSpace::World);
		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(LocationComponent,NewLocation);
		FRotator CarRotation = OwnerCar->GetVehicleBodyRotation();
		
		float YawRotation = UKismetMathLibrary::NormalizedDeltaRotator(NewRotation,CarRotation).Yaw;
		
		float NewClampedRot = UKismetMathLibrary::MapRangeClamped(YawRotation, -10,10,-1,1);

		OwnerCar->SteerRight(NewClampedRot);
	}
}
