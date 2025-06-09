// Copyright 2025 Mateusz Wozniak. All Rights Reserved.


#include "SRCarPawn.h"
#include "Kismet/KismetMathLibrary.h"

static TAutoConsoleVariable<int32> CVarCarDebug(
	TEXT("car.CarDebug"),
	1,
	TEXT("Debug visualisation for car movment.\n")
	TEXT("<=0: off \n")
	TEXT(" 1: Forward Debuging\n")
	TEXT(" 2: Steer Debuging\n"),
	ECVF_Scalability | ECVF_RenderThreadSafe);

ASRCarPawn::ASRCarPawn()
{
	FrontLeftSuspensionComp = CreateDefaultSubobject<USRVehicleSuspensionComponent>(TEXT("FrontLeft"));
	FrontRightSuspensionComp = CreateDefaultSubobject<USRVehicleSuspensionComponent>(TEXT("FrontRight"));

	RearLeftSuspensionComp = CreateDefaultSubobject<USRVehicleSuspensionComponent>(TEXT("RearLeft"));
	RearRightSuspensionComp = CreateDefaultSubobject<USRVehicleSuspensionComponent>(TEXT("RearRight"));
	
	FrontLeftSuspensionComp->SetupAttachment(VehicleBody);
	FrontRightSuspensionComp->SetupAttachment(VehicleBody);
	RearLeftSuspensionComp->SetupAttachment(VehicleBody);
	RearRightSuspensionComp->SetupAttachment(VehicleBody);

	FrontLeftSuspensionComp->SetVehicleMainBody(VehicleBody);
	FrontRightSuspensionComp->SetVehicleMainBody(VehicleBody);
	RearLeftSuspensionComp->SetVehicleMainBody(VehicleBody);
	RearRightSuspensionComp->SetVehicleMainBody(VehicleBody);
	
}

void ASRCarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	VehicleAcceleration -= 0.01f;
	VehicleAcceleration = FMath::Clamp(VehicleAcceleration, 0, 1);
}


void ASRCarPawn::MoveForward(float Value)
{
	if (FMath::Abs(Value) < 0.3f)
	{
		return;
	}

	FVector NormalizeForwardSurface;
	bool bOnGround = LineTraceParallelSurfaceVector(VehicleBody,100,NormalizeForwardSurface);

	
	if(bOnGround)
	{
		VehicleAcceleration += 0.02f * FMath::Abs(Value);
		VehicleAcceleration = FMath::Clamp(VehicleAcceleration, 0, 1);
		
		float MaxSpeedMetersPerSecond  = ((MaxSpeedKph * 1000) / 3600);
		float MaxSpeedForce = MaxSpeedMetersPerSecond * VehicleBody->GetMass() * FMath::Pow((10 * VehicleBody->GetLinearDamping()),2);

		float ZDegree = FMath::Abs(VehicleBody->GetPhysicsAngularVelocityInDegrees().Z);
		float NormalizedZDegree = FMath::Abs(UKismetMathLibrary::NormalizeToRange(ZDegree,80,180));
		float AxisStrenght = ZDegree > 60 ? (1 - NormalizedZDegree) : 1;
		
		FVector Force =  NormalizeForwardSurface * (Value * MaxSpeedForce * CurveAccelerationEngine->GetFloatValue(VehicleAcceleration));
		Force *= AxisStrenght;
		
		FVector LocationForce = Value > 0 ? FVector(200,0, -15) : FVector(-200, 0, -15);
		LocationForce = VehicleBody->GetComponentTransform().TransformPosition(LocationForce);
		
		VehicleBody->AddForceAtLocation(Force, LocationForce);


		if(CVarCarDebug.GetValueOnGameThread() == 1)
		{
			FString VecString = FString::SanitizeFloat(AxisStrenght); //NormalizeForwardSurface.ToString()
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, VecString);

			DrawDebugDirectionalArrow(GetWorld(), LocationForce, Force, 4, FColor::Red, false, 0.1f);
		}
	}

	
}


void ASRCarPawn::SteerRight(float Value)
{
	if (FMath::Abs(Value) < 0.3f)
	{
		return;
	}


	if (VehicleBody)
	{
		float Strenghht = 9000000000.0 * 6 * Value;
		
		FVector Torque = VehicleBody->GetUpVector() * Strenghht;


		VehicleBody->AddTorqueInDegrees(Torque);
	}
}

