// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Game/SRGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "SRMenuUserWidget.generated.h"

UCLASS()
class SIMPLERACING_API USRMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly)
	USRGameInstance* SRGameInstance;
};
