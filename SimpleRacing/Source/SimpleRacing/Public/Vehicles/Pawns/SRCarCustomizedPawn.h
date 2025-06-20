// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Vehicles/Pawns/SRCarPawn.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SkeletalMeshComponent.h"
#include "SRCarCustomizedPawn.generated.h"

UCLASS()
class SIMPLERACING_API ASRCarCustomizedPawn : public ASRCarPawn
{
	GENERATED_BODY()

public:
	
	ASRCarCustomizedPawn();
	
protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CarSkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* InteriorMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* DoorLeftMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* DoorRightMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* MainBodyMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* BumperFrontMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* BumperRearMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* HoodFrontMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* CockpitConsoleMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* SteeringWheelMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* DiffuserRearMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* FenderRightMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* FenderLeftMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* BootRearMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
    UStaticMeshComponent* SpoilerBackMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* WindowExteriorInteriorMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* WingMirrorRightMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CarPart, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* WingMirrorLeftMeshComponent;
	
	float CurrentSteeringWheelAngle = 0;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* DefaultCarMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicCarBodyMaterial;

	UFUNCTION()
	void SetDynamicMaterialCarParts();
	
	virtual void SetDamage(float Damage) override;

	void SetCarTextureMaterial(UTexture2D* NewTexture);

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UTexture2D*> CarColorTexture;
};
