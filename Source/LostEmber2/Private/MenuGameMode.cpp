#include "MenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AMenuGameMode::AMenuGameMode()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {
        MenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);

        if (MenuWidgetInstance)
        {
            MenuWidgetInstance->AddToViewport();
        }
    }

	// Desactivate player input and show mouse cursor
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        PC->SetShowMouseCursor(true);
        PC->SetInputMode(FInputModeUIOnly());
    }
}