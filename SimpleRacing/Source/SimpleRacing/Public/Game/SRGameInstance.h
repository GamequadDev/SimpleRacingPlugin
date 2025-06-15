// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SRGameInstance.generated.h"

UENUM(BlueprintType)
enum class EGameMode : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Racing = 1 UMETA(DisplayName = "Racing"),
	Training  = 2  UMETA(DisplayName = "Training"),
};

UCLASS()
class SIMPLERACING_API USRGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EGameMode SelectedGameMode = EGameMode::None;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxTime = 100.0f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int NumberLoop = 1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int VehicleColor = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bEndSuccess = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FTimespan> EndLoopsTime;
};