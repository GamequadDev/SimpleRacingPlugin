// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SRVehiclePlayerHUD.generated.h"

UCLASS()
class SIMPLERACING_API USRVehiclePlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Owner)
	class ASRVehiclePawn* OwnerVehiclePawn;
};
