#include "MenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"

AMenuGameMode::AMenuGameMode()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (MainMenuWidgetClass)
    {
        UMainMenuWidget* MenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
        }
    }

    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        PC->bShowMouseCursor = true;
        PC->SetInputMode(FInputModeUIOnly());
    }
}