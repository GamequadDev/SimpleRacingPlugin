// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Pawn.h"
#include "Track/SRTrackPath.h"
#include "Game/SRGameInstance.h"
#include "TimerManager.h"
#include "UI/UMG/SRVehiclePlayerHUD.h"
#include "SRVehiclePawn.generated.h"

UCLASS()
class SIMPLERACING_API ASRVehiclePawn : public APawn
{
	GENERATED_BODY()

public:
	
	ASRVehiclePawn();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Suspension, meta=(AllowPrivateAccess = "true"))
	USceneComponent* SceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Suspension, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* VehicleBody;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	UCameraComponent* CameraThirdPerson;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	UCameraComponent* CameraFirstPeron;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parameters)
	float VehicleAcceleration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Parameters, meta = (AllowPrivateAccess = "true"))
	float MaxSpeedKph = 150;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Parameters, meta=(AllowPrivateAccess = "true"))
	float MinHitSpeedKph = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Parameters, meta=(AllowPrivateAccess = "true"))
	float CurrentDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Parameters, meta=(AllowPrivateAccess = "true"))
	float SteerForceStrength = 1000;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters, meta = (AllowPrivateAccess = "true"))
	UCurveFloat* CurveAccelerationEngine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Time, meta=(AllowPrivateAccess = "true"))
	FTimespan CurrentRacingTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Time, meta=(AllowPrivateAccess = "true"))
	TArray<FTimespan> RegisterLoopTime;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Time, meta=(AllowPrivateAccess = "true"))
	int CurrentLoop = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AI, meta=(AllowPrivateAccess = "true"))
	bool bAIBot = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<USRVehiclePlayerHUD> PlayerWidgetClass;
	
	UPROPERTY()
	USRVehiclePlayerHUD* PlayerWidgetInstance;
	
	UPROPERTY()
	USRGameInstance* GameInstance = nullptr;
	
	UPROPERTY()
	FTimerHandle RacingTimerHandle;

	UPROPERTY()
	class APlayerController* PlayerController;
	
	UFUNCTION()
	bool LineTraceParallelSurfaceVector(USceneComponent* Component, float HeightCar, FVector& VectorNormalize, FHitResult &Hit);

	UFUNCTION()    
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	virtual  void SetDamage(float Damage);

	UFUNCTION()
	void EndGame(bool bSuccess);

public:	

	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	ASRTrackPath* TrackPathActor;

	UPROPERTY()
	int CurrentPoint = 0;
	
	UFUNCTION()
	FVector GetVehicleBodyLocation() const {return VehicleBody->GetComponentLocation();};

	UFUNCTION()
	FRotator GetVehicleBodyRotation() const {return VehicleBody->GetComponentRotation();};
	
	UFUNCTION()
	virtual void SteerRight(float Value){};
	
	UFUNCTION()
	virtual void MoveForward(float Value){};

	UFUNCTION()
	virtual void CameraRotationX(float Value);
	
	UFUNCTION()
	void StartRacingTimer();

	UFUNCTION()
	void UpdateRacingTimer();

	UFUNCTION()
	void StopRacingTimer();

	UFUNCTION(BlueprintPure)
	FTimespan GetRacingTimer(){return CurrentRacingTime;}
	 
	UFUNCTION()
	void ChangeCamera();
	
	UFUNCTION(BlueprintPure)
	float GetSpeedKph();
	
	UFUNCTION()
	float GetSpeedMps();
};
