// Copyright 2025 Mateusz Wozniak. All Rights Reserved.


#include "Game/SRGameMode.h"

void ASRGameMode::DisplaySummaryWidget()
{
	if(SummaryWidgetClass)
	{
		SummaryWidgetInstance = CreateWidget<USRMenuUserWidget>(GetWorld(), SummaryWidgetClass);
		if (SummaryWidgetInstance)
		{
			SummaryWidgetInstance->AddToViewport();
		}
	}
}
