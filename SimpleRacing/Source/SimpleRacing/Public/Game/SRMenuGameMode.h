// Copyright 2025 Mateusz Wozniak. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/UMG/SRMenuUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "SRMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLERACING_API ASRMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	
	
public:
    
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<USRMenuUserWidget> MenuWidgetClass;
	
	UPROPERTY()
	USRMenuUserWidget* MenuWidgetInstance;	
	
};
