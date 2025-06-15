// Copyright 2025 Mateusz Wozniak. All Rights Reserved.


#include "UI/UMG/SRMenuUserWidget.h"

void USRMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UGameInstance* GameInstance = GetGameInstance();
	if(GameInstance)
	{
		SRGameInstance = Cast<USRGameInstance>(GameInstance);
	}
}