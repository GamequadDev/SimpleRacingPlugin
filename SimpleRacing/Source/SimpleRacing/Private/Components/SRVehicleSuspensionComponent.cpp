// Copyright 2025 Teyon. All Rights Reserved.


#include "Components/SRVehicleSuspensionComponent.h"

// Sets default values for this component's properties
USRVehicleSuspensionComponent::USRVehicleSuspensionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//RootComponent->AttachToComponent(RootComponent);
	
	// ...
}


// Called when the game starts
void USRVehicleSuspensionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USRVehicleSuspensionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	const FVector ComponentWorldLocation = GetComponentLocation();
	
	if(VehicleMainBody)
	{
		FHitResult Hit;

		
		TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_WorldStatic;
		
		const FVector TracerStart = ComponentWorldLocation;
		const FVector TracerEnd = FVector(TracerStart.X,TracerStart.Y,TracerStart.Z - LenghtSuspension);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(VehicleMainBody->GetOwner());
		
		GetWorld()->LineTraceSingleByChannel(Hit, TracerStart, TracerEnd, TraceChannelProperty, QueryParams);

	

		if (Hit.bBlockingHit)
		{
			const FVector SuspensionVelocity = VehicleMainBody->GetPhysicsLinearVelocityAtPoint(ComponentWorldLocation);
			const float SuspensionVelocityUp = FVector::DotProduct(SuspensionVelocity, VehicleMainBody->GetUpVector());
			
			const float CompressionRatio = 1 - (Hit.Distance / LenghtSuspension);
			const float SuspensionForce = SpringForce * CompressionRatio;
			
			const float DeltaSuspensionForce = SuspensionForce - (SuspensionVelocityUp * SpringDumbing);
			
			const FVector ForceVector = FVector(0,0,DeltaSuspensionForce);
			
			VehicleMainBody->AddForceAtLocation(ForceVector,ComponentWorldLocation);

			LastHitDistance = Hit.Distance;

			if(bDebugMode)
			{
				FString FloatAsString = FString::SanitizeFloat(CompressionRatio);
				DrawDebugString(GetWorld(), TracerEnd, *FloatAsString, GetOwner(), FColor::Black, 0.1f,true);
			}
		}
		else
		{
			LastHitDistance = LenghtSuspension + 40;
		}

		if(bDebugMode)
		{
			DrawDebugLine(GetWorld(), TracerStart, TracerEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 0.1f, 0, 4.0f);
		}
		
	}
}

void USRVehicleSuspensionComponent::SetVehicleMainBody(UStaticMeshComponent* Vehicle)
{
	VehicleMainBody = Vehicle;
}

