// Copyright 2025 Mateusz Wozniak. All Rights Reserved.


#include "Vehicles/Pawns/SRVehiclePawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SRGameMode.h"

ASRVehiclePawn::ASRVehiclePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SceneRoot->SetupAttachment(RootComponent);
	
	VehicleBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleBody"));
	VehicleBody->SetupAttachment(SceneRoot);

	VehicleBody->SetSimulatePhysics(true);
	VehicleBody->SetMassOverrideInKg(NAME_None,1000.0f);
	VehicleBody->SetNotifyRigidBodyCollision(true);
	
	SpringComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringComp->SetupAttachment(VehicleBody);
	SpringComp->TargetArmLength = 800.0f;
	SpringComp->SetRelativeRotation(FRotator(-30,0,0));
	
	SpringComp->bDoCollisionTest = false;
	
	CameraThirdPerson = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraThirdPerson"));
	CameraFirstPeron = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraFirstPerson"));
	
	CameraThirdPerson->SetupAttachment(SpringComp, USpringArmComponent::SocketName);
	CameraFirstPeron->SetupAttachment(VehicleBody);
}

void ASRVehiclePawn::BeginPlay()
{
	Super::BeginPlay();

	CameraThirdPerson->SetActive(true);
	CameraFirstPeron->Deactivate();
	
	VehicleBody->OnComponentHit.AddDynamic(this, &ASRVehiclePawn::OnHit);
	
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(),ASRTrackPath::StaticClass());
    if(FoundActor)
    {
    	TrackPathActor = Cast<ASRTrackPath>(FoundActor);
    }

	if(PlayerWidgetClass and !bAIBot)
	{
		PlayerWidgetInstance = CreateWidget<USRVehiclePlayerHUD>(GetWorld(), PlayerWidgetClass);
		if (PlayerWidgetInstance)
		{
			PlayerWidgetInstance->OwnerVehiclePawn = this;
			PlayerWidgetInstance->AddToViewport();
		}
	}

	PlayerController = Cast<APlayerController>(GetController());
	GameInstance = Cast<USRGameInstance>(GetGameInstance());
}

void ASRVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ASRVehiclePawn::CameraRotationX(float Value)
{
	if (FMath::Abs(Value) < 0.3f)
	{
		return;
	}
	
	FRotator AddedRotation = FRotator(SpringComp->GetRelativeRotation().Pitch,SpringComp->GetRelativeRotation().Yaw + Value,0);
	SpringComp->SetRelativeRotation(AddedRotation);
}

float ASRVehiclePawn::GetSpeedKph()
{
	const FVector ComponentVelocity = VehicleBody->GetComponentVelocity();
	const float SpeedMps = FVector::DotProduct(ComponentVelocity,VehicleBody->GetForwardVector());
	const float SpeedKph = ((SpeedMps /10) * 1000) / 3600;
	
	return SpeedKph;
}

float ASRVehiclePawn::GetSpeedMps()
{
	const FVector ComponentVelocity = VehicleBody->GetComponentVelocity();
	const float SpeedMps = FVector::DotProduct(ComponentVelocity,VehicleBody->GetForwardVector());
	
	return SpeedMps;
}

bool ASRVehiclePawn::LineTraceParallelSurfaceVector(USceneComponent* Component,float HeightCar,FVector& VectorNormalize, FHitResult &Hit)
{
	const FVector LocationWorld = Component->GetComponentLocation();

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

void ASRVehiclePawn::ChangeCamera()
{
	
	if(CameraThirdPerson->IsActive())
	{
		CameraFirstPeron->SetActive(true);	
		CameraThirdPerson->Deactivate();
	}
	else
	{
		CameraThirdPerson->SetActive(true);
        CameraFirstPeron->Deactivate();	
	}
}

void ASRVehiclePawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	const float ForceMin = VehicleBody->GetMass() * 100 * MinHitSpeedKph;
	const float ForceHit = NormalImpulse.GetAbs().X + NormalImpulse.GetAbs().Y;
	
	if (ForceHit > ForceMin)
	{
		const float ForceHitToNormalized = (ForceHit * 2) / (VehicleBody->GetMass() * 100);
		const float NormalizeForceHit = UKismetMathLibrary::NormalizeToRange(ForceHitToNormalized,MinHitSpeedKph,MaxSpeedKph);
		
		SetDamage(NormalizeForceHit);
	}
}

void ASRVehiclePawn::SetDamage(float Damage)
{
	if (CurrentDamage + Damage > 1)
	{
		CurrentDamage = 1;
	}
	else
	{
		CurrentDamage +=Damage;
	}
}

void ASRVehiclePawn::StartRacingTimer()
{
	if(bAIBot)
	{
		return;
	}
	
	CurrentLoop += 1;
	
	if(GetWorld()->GetTimerManager().IsTimerActive(RacingTimerHandle) && GameInstance->SelectedGameMode == EGameMode::Training)
	{
		FTimespan LoopTime = CurrentRacingTime;
		RegisterLoopTime.Add(LoopTime);
		StopRacingTimer();
		EndGame(true);
		return;
	}
	
	if(GetWorld()->GetTimerManager().IsTimerActive(RacingTimerHandle) && GameInstance->SelectedGameMode == EGameMode::Racing)
	{
		FTimespan LoopTime = CurrentRacingTime;
		RegisterLoopTime.Add(LoopTime);
		
		if(CurrentLoop == (GameInstance->NumberLoop + 1))
		{
			StopRacingTimer();
			EndGame(true);
			return;
		}
	}

	
	if(!(GetWorld()->GetTimerManager().IsTimerActive(RacingTimerHandle)))
	{
		CurrentRacingTime = FTimespan::Zero(); 
		GetWorld()->GetTimerManager().SetTimer(RacingTimerHandle, this, &ASRVehiclePawn::UpdateRacingTimer, 0.1f, true);
	}
}

void ASRVehiclePawn::UpdateRacingTimer()
{
	if(CurrentRacingTime.GetSeconds() >= GameInstance->MaxTime && GameInstance->SelectedGameMode == EGameMode::Training)
	{
		StopRacingTimer();
		EndGame(false);
		return;
	}
	CurrentRacingTime = CurrentRacingTime + FTimespan::FromSeconds(0.1);
}

void ASRVehiclePawn::StopRacingTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(RacingTimerHandle);
}

void ASRVehiclePawn::EndGame(bool bSuccess)
{
	GameInstance->bEndSuccess = bSuccess;
	GameInstance->EndLoopsTime = RegisterLoopTime;

	PlayerWidgetInstance->RemoveFromParent();

	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	ASRGameMode* SRGameMode = Cast<ASRGameMode>(GameMode);
	if(SRGameMode)
	{
		SRGameMode->DisplaySummaryWidget();
	}

	Destroy();
}