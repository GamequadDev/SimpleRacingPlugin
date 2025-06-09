// Copyright 2025 Mateusz Wozniak. All Rights Reserved.


#include "Vehicles/Pawns/SRVehiclePawn.h"


ASRVehiclePawn::ASRVehiclePawn()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SceneRoot->SetupAttachment(RootComponent);
	
	VehicleBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleBody"));
	VehicleBody->SetupAttachment(SceneRoot);

	VehicleBody->SetSimulatePhysics(true);
	VehicleBody->SetMassOverrideInKg(NAME_None,1000.0f);
}


void ASRVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASRVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
//void ASRVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//VehicleBody->GetComponentVelocity()
	//const float SuspensionVelocityUp = FVector::DotProduct(SuspensionVelocity, VehicleMainBody->GetUpVector());

	
//}

float ASRVehiclePawn::GetSpeedKph()
{
	const FVector ComponentVelocity = VehicleBody->GetComponentVelocity();
	const float SpeedMps = FVector::DotProduct(ComponentVelocity,VehicleBody->GetForwardVector());
	const float SpeedKph = (SpeedMps * 1000) / 3600;
	
	return SpeedKph;
}

bool ASRVehiclePawn::LineTraceParallelSurfaceVector(USceneComponent* Component,float HeightCar,FVector& VectorNormalize)
{
	const FVector LocationWorld = Component->GetComponentLocation();
	FHitResult Hit;
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_WorldStatic;
		
	const FVector TracerStart = LocationWorld;
	const FVector TracerEnd = FVector(TracerStart.X,TracerStart.Y,TracerStart.Z - HeightCar);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
		
	GetWorld()->LineTraceSingleByChannel(Hit, TracerStart, TracerEnd, TraceChannelProperty, QueryParams);
	if (Hit.bBlockingHit)
	{
		FVector Forward = Component->GetForwardVector();
	
		FVector ForwardSurface = FVector::VectorPlaneProject(Forward,Hit.ImpactNormal);
	
		VectorNormalize = ForwardSurface.GetSafeNormal();
		
		return true;
	}
	return false;
}