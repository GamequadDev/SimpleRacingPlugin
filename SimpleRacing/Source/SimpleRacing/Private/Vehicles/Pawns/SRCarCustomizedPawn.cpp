// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#include "Vehicles/Pawns/SRCarCustomizedPawn.h"

ASRCarCustomizedPawn::ASRCarCustomizedPawn()
{
	CarSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CarSkeletalMeshComponent"));
	CarSkeletalMeshComponent->SetupAttachment(VehicleBody);

	SceneWheelForwardLeftComponent->SetupAttachment(CarSkeletalMeshComponent, "wheel_front_left_spin");
	SceneWheelForwardRightComponent->SetupAttachment(CarSkeletalMeshComponent, "wheel_front_right_spin");

	WheelRearLeftMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"wheel_back_left_spin");
	WheelRearRightMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"wheel_back_right_spin");

	SuspensionFrontLeftComponent->SetupAttachment(CarSkeletalMeshComponent, "wheel_front_left_spin");
	SuspensionFrontRightComponent->SetupAttachment(CarSkeletalMeshComponent, "wheel_front_right_spin");
	SuspensionRearLeftComponent->SetupAttachment(CarSkeletalMeshComponent,"wheel_back_left_spin");
	SuspensionRearRightComponent->SetupAttachment(CarSkeletalMeshComponent,"wheel_back_right_spin");

	InteriorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteriorMeshComponent"));
	InteriorMeshComponent->SetupAttachment(CarSkeletalMeshComponent);
	
	CameraFirstPeron->SetupAttachment(CarSkeletalMeshComponent, "CarInteriorGameplayCamera");
	
	DoorLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorLeftMeshComponent"));
	DoorRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorRightMeshComponent"));
	
	DoorLeftMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"door_left");
	DoorRightMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"door_right");
	
	MainBodyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBodyMeshComponent"));
	MainBodyMeshComponent->SetupAttachment(CarSkeletalMeshComponent);
	
	BumperFrontMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BumperFrontMeshComponent"));
	BumperFrontMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"bumper_front");
	
	BumperRearMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BumperRearMeshComponent"));
	BumperRearMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"bumper_rear");
	
	HoodFrontMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HoodFrontMeshComponent"));
	HoodFrontMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"hood_front");
	
	CockpitConsoleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CockpitConsoleMeshComponent"));
	CockpitConsoleMeshComponent->SetupAttachment(CarSkeletalMeshComponent);
	
	SteeringWheelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SteeringWheelMeshComponent"));
	SteeringWheelMeshComponent->SetupAttachment(InteriorMeshComponent,"SteeringWheel");

	DiffuserRearMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DiffuserRearMeshComponent"));
	DiffuserRearMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"diffuser_back");
	
	FenderRightMeshComponent= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FenderRightMeshComponent"));
	FenderRightMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"fender_right");

	FenderLeftMeshComponent= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FenderLeftMeshComponent"));
	FenderLeftMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"fender_left");
	
	
	BootRearMeshComponent= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BootRearMeshComponent"));
	BootRearMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"boot_rear");
	
	SpoilerBackMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpoilerBackMeshComponent"));
	SpoilerBackMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"spoiler_back");

	WindowExteriorInteriorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WindowExteriorInteriorMeshComponent"));
	WindowExteriorInteriorMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"hood_front");

	WingMirrorRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WingMirrorRightMeshComponent"));
	WingMirrorRightMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"wing_mirror_right");

	WingMirrorLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WingMirrorLeftMeshComponent"));
	WingMirrorLeftMeshComponent->SetupAttachment(CarSkeletalMeshComponent,"wing_mirror_left");
}

void ASRCarCustomizedPawn::BeginPlay()
{
	Super::BeginPlay();

	SetDynamicMaterialCarParts();
}

void ASRCarCustomizedPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentSteeringWheelAngle = FMath::FInterpTo(CurrentSteeringWheelAngle, TargetSteerAngle, DeltaTime, 10);
	SteeringWheelMeshComponent->SetRelativeRotation(FRotator(0, 0, CurrentSteeringWheelAngle));
}

void ASRCarCustomizedPawn::SetDamage(float Damage)
{
	Super::SetDamage(Damage);

    if(DynamicCarBodyMaterial)
    {
        DynamicCarBodyMaterial->SetScalarParameterValue("DamageValue",CurrentDamage);
    }
}

void ASRCarCustomizedPawn::SetDynamicMaterialCarParts()
{
	if(DefaultCarMaterialInstance)
	{
		DynamicCarBodyMaterial = UMaterialInstanceDynamic::Create(DefaultCarMaterialInstance, this);
        	
        	DoorLeftMeshComponent->SetMaterial(0, DynamicCarBodyMaterial);
        	DoorRightMeshComponent->SetMaterial(0, DynamicCarBodyMaterial);
        	
        	MainBodyMeshComponent->SetMaterial(0, DynamicCarBodyMaterial);
        	HoodFrontMeshComponent->SetMaterial(0, DynamicCarBodyMaterial);
        	BumperFrontMeshComponent->SetMaterial(0, DynamicCarBodyMaterial);
        	BumperRearMeshComponent->SetMaterial(0, DynamicCarBodyMaterial);
        	FenderRightMeshComponent->SetMaterial(0, DynamicCarBodyMaterial);
        	FenderLeftMeshComponent->SetMaterial(0, DynamicCarBodyMaterial);
        	BootRearMeshComponent->SetMaterial(0, DynamicCarBodyMaterial);
        	SpoilerBackMeshComponent->SetMaterial(0, DynamicCarBodyMaterial);
	}
	
	if(GameInstance && DynamicCarBodyMaterial)
	{
		if(CarColorTexture.IsValidIndex(GameInstance->VehicleColor))
		{
			SetCarTextureMaterial(CarColorTexture[GameInstance->VehicleColor]);
		}
	}
}

void ASRCarCustomizedPawn::SetCarTextureMaterial(UTexture2D* NewTexture)
{
	if(DynamicCarBodyMaterial)
	{
		DynamicCarBodyMaterial->SetTextureParameterValue("Albedo",NewTexture);
	}
}