// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#include "Components/SRVehicleSuspensionComponent.h"

static TAutoConsoleVariable<int32> CVarSuspensionDebug(
	TEXT("vehicle.Suspension"),
	0,
	TEXT("Debug visualisation for suspension.\n")
	TEXT("<=0: off \n")
	TEXT(" 1: Suspension Visualition Raycast\n")
	TEXT(" 2: Suspension Visualition Value\n"),
	ECVF_Scalability | ECVF_RenderThreadSafe);

USRVehicleSuspensionComponent::USRVehicleSuspensionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

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

			if(CVarSuspensionDebug.GetValueOnGameThread() == 2)
			{
				FString FloatAsString = FString::SanitizeFloat(CompressionRatio);
				DrawDebugString(GetWorld(), TracerEnd, *FloatAsString, GetOwner(), FColor::Black, 0.1f,true);
			}
		}
		else
		{
			LastHitDistance = LenghtSuspension + 40;
		}

		if(CVarSuspensionDebug.GetValueOnGameThread() == 1)
		{
			DrawDebugLine(GetWorld(), TracerStart, TracerEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 0.1f, 0, 4.0f);
		}
	}
}

void USRVehicleSuspensionComponent::SetVehicleMainBody(UStaticMeshComponent* Vehicle)
{
	VehicleMainBody = Vehicle;
}