// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/UMG/SRMenuUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "SRGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLERACING_API ASRGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<USRMenuUserWidget> SummaryWidgetClass;
	
	UPROPERTY()
	USRMenuUserWidget* SummaryWidgetInstance;	
	
	UFUNCTION()
	void DisplaySummaryWidget();
	
};
