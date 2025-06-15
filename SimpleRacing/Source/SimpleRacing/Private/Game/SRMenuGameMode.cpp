// Copyright 2025 Mateusz Wozniak. All Rights Reserved.

#include "Game/SRMenuGameMode.h"

void ASRMenuGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    if(MenuWidgetClass)
    {
        MenuWidgetInstance = CreateWidget<USRMenuUserWidget>(GetWorld(), MenuWidgetClass);
    	if (MenuWidgetInstance)
        {
           MenuWidgetInstance->AddToViewport();
        }
    }
}