// Copyright 2025 Mateusz Wozniak. All Rights Reserved.


#include "Vehicles/Pawns/SRCarPawn.h"
#include "Kismet/KismetMathLibrary.h"

static TAutoConsoleVariable<int32> CVarCarDebug(
	TEXT("car.CarDebug"),
	0,
	TEXT("Debug visualisation for car movment.\n")
	TEXT("<=0: off \n")
	TEXT(" 1: Forward Debuging\n")
	TEXT(" 2: Steer Debuging\n")
	TEXT(" 3: Wheel\n"),
	ECVF_Scalability | ECVF_RenderThreadSafe);

ASRCarPawn::ASRCarPawn()
{
	SuspensionFrontLeftComponent = CreateDefaultSubobject<USRVehicleSuspensionComponent>(TEXT("SuspensionFrontLeftComponent"));
	SuspensionFrontRightComponent = CreateDefaultSubobject<USRVehicleSuspensionComponent>(TEXT("SuspensionFrontRightComponent"));
	SuspensionRearLeftComponent = CreateDefaultSubobject<USRVehicleSuspensionComponent>(TEXT("SuspensionRearLeftComponent"));
	SuspensionRearRightComponent = CreateDefaultSubobject<USRVehicleSuspensionComponent>(TEXT("SuspensionRearRightComponent"));
	
	SuspensionFrontLeftComponent->SetupAttachment(VehicleBody);
	SuspensionFrontRightComponent->SetupAttachment(VehicleBody);
	SuspensionRearLeftComponent->SetupAttachment(VehicleBody);
	SuspensionRearRightComponent->SetupAttachment(VehicleBody);

	SuspensionFrontLeftComponent->SetVehicleMainBody(VehicleBody);
	SuspensionFrontRightComponent->SetVehicleMainBody(VehicleBody);
	SuspensionRearLeftComponent->SetVehicleMainBody(VehicleBody);
	SuspensionRearRightComponent->SetVehicleMainBody(VehicleBody);

	WheelFrontLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelFrontLeftMeshComponent"));
	WheelFrontRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelFrontRightMeshComponent"));
	WheelRearLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRearLeftMeshComponent"));
	WheelRearRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRearRightMeshComponent"));

	SceneWheelForwardLeftComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneWheelForwardLeft"));
	SceneWheelForwardRightComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneWheelForwardRight"));

	SceneWheelForwardLeftComponent->SetupAttachment(VehicleBody);
	SceneWheelForwardRightComponent->SetupAttachment(VehicleBody);
	
	WheelFrontLeftMeshComponent->SetupAttachment(SceneWheelForwardLeftComponent);
	WheelFrontRightMeshComponent->SetupAttachment(SceneWheelForwardRightComponent);
	
	WheelRearLeftMeshComponent->SetupAttachment(VehicleBody);
	WheelRearRightMeshComponent->SetupAttachment(VehicleBody);
	
	
	WheelFrontLeftMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WheelFrontRightMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WheelRearLeftMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WheelRearRightMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void ASRCarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentSteerAngle = FMath::FInterpTo(CurrentSteerAngle, TargetSteerAngle, DeltaTime, 10);
	
	SceneWheelForwardLeftComponent->SetRelativeRotation(FRotator(0, CurrentSteerAngle, 0));
	SceneWheelForwardRightComponent->SetRelativeRotation(FRotator(0, CurrentSteerAngle, 0));

	TargetSteerAngle > 0 ?	TargetSteerAngle -= 1: TargetSteerAngle += 1;
	
	VehicleAcceleration -= 0.01f;
	VehicleAcceleration = FMath::Clamp(VehicleAcceleration, 0, 1);

	float WheelSpeed = (GetSpeedMps() * DeltaTime * 100) / (2 * 3.14 * 20);
	FRotator RotationNew = FRotator(-WheelSpeed,0,0);
	FRotator FrontRotation = FRotator(-WheelSpeed,0,0);
	
	if(CVarCarDebug.GetValueOnGameThread() == 3)
	{
		FString VecString = FString::SanitizeFloat(WheelSpeed);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, VecString);
	}
	
	WheelFrontLeftMeshComponent->AddLocalRotation(FrontRotation);
	WheelFrontRightMeshComponent->AddLocalRotation(FrontRotation);
	WheelRearLeftMeshComponent->AddLocalRotation(RotationNew);
	WheelRearRightMeshComponent->AddLocalRotation(RotationNew);
	
	UpdateVehicleForce(ForwardAxisValue);
}

void ASRCarPawn::MoveForward(float Value)
{
	ForwardAxisValue = Value;
	
	if (FMath::Abs(Value) < 0.3f)
	{
		return;
	}
	
	VehicleAcceleration += 0.02f * FMath::Abs(Value);
	VehicleAcceleration = FMath::Clamp(VehicleAcceleration, 0, 1);
}

void ASRCarPawn::SteerRight(float Value)
{
	if (FMath::Abs(Value) < 0.3f)
	{
		return;
	}
	
	TargetSteerAngle = Value * 30;

	VehicleAcceleration -= 0.01f;
	VehicleAcceleration = FMath::Clamp(VehicleAcceleration, 0, 1);

	if (FMath::Abs(GetSpeedMps()) < 1)
	{
		return;
	}
	
	if(CVarCarDebug.GetValueOnGameThread() == 3)
	{
		FString VecString = FString::SanitizeFloat(TargetSteerAngle);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, VecString);
	}
	
	if (VehicleBody)
	{
		float InertiaTensor =  VehicleBody->GetInertiaTensor().Z;
		
		float Strenghht = InertiaTensor * SteerForceStrength * Value;
		FVector Torque = VehicleBody->GetUpVector() * Strenghht;
		
		VehicleBody->AddTorqueInDegrees(Torque);
	}
}

void ASRCarPawn::UpdateVehicleForce(float Value)
{
	FHitResult Hit;
	FVector NormalizeForwardSurface;
    	
	bool bOnGround = LineTraceParallelSurfaceVector(VehicleBody,100,NormalizeForwardSurface,Hit);
    	
	if(bOnGround && CurveAccelerationEngine)
	{
		float MaxSpeedMetersPerSecond  = ((MaxSpeedKph * 1000) / 3600);
		float MaxSpeedForce = MaxSpeedMetersPerSecond * VehicleBody->GetMass() * FMath::Pow((10 * VehicleBody->GetLinearDamping()),2);
    		
		float Friction = 1.0f;
		if(TrackPathActor)
		{
			FVector VehicleLocation = VehicleBody->GetComponentLocation();
    			
			float DistanceCloset = TrackPathActor->TrackPath->GetDistanceAlongSplineAtLocation(VehicleLocation, ESplineCoordinateSpace::World);
			FVector LocationCloset =  TrackPathActor->TrackPath->GetLocationAtDistanceAlongSpline(DistanceCloset,ESplineCoordinateSpace::World);
    
			float Distance = FVector::Distance(LocationCloset,VehicleLocation);
    			
			if(Distance > 600)
			{
				Friction = 0.5f;
					
				if (PlayerController)
				{
					PlayerController->PlayDynamicForceFeedback(0.5f,0.1f,true, true,true,EDynamicForceFeedbackAction::Start);
				}
				if(Distance > 3000)
				{
					EndGame(false);
				}
			}
    	}
		float MaxSpeedForceWithDamage = MaxSpeedForce * Friction * (1 - (CurrentDamage * 0.5));
    		
		float ZDegree = FMath::Abs(VehicleBody->GetPhysicsAngularVelocityInDegrees().Z);
		float NormalizedZDegree = FMath::Abs(UKismetMathLibrary::NormalizeToRange(ZDegree,80,180));
		float AxisStrenght = ZDegree > 60 ? (1 - NormalizedZDegree) : 1;
    		
		FVector Force =  NormalizeForwardSurface * (Value * MaxSpeedForceWithDamage * CurveAccelerationEngine->GetFloatValue(VehicleAcceleration));
		Force *= AxisStrenght;
    		
		FVector LocationForce = Value > 0 ? FVector(50,0, -15) : FVector(-30, 0, -15);
		LocationForce = VehicleBody->GetComponentTransform().TransformPosition(LocationForce);
    		
		VehicleBody->AddForceAtLocation(Force, LocationForce);
    		
		if(CVarCarDebug.GetValueOnGameThread() == 1)
		{
			FString VecString = FString::SanitizeFloat(AxisStrenght);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, VecString);
    
			DrawDebugDirectionalArrow(GetWorld(), LocationForce, Force, 4, FColor::Red, false, 0.1f);
		}
	}
}