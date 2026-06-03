#include "LostEmberGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

ALostEmberGameMode::ALostEmberGameMode()
{
    PrimaryActorTick.bCanEverTick = true;

    ActivatedLightCount = 0;
    TotalRequiredLights = 3;

    MaxTime = 180.0f; // 3 minutes
    CurrentTime = MaxTime;

    bIsGameOver = false;
    bIsWin = false;

    GameHUDInstance = nullptr;
    WinWidgetInstance = nullptr;
    GameOverWidgetInstance = nullptr;
}

void ALostEmberGameMode::BeginPlay()
{
    Super::BeginPlay();

    ActivatedLightCount = 0;
    CurrentTime = MaxTime;
    bIsGameOver = false;
    bIsWin = false;

    // Spawn HUD
    if (GameHUDClass)
    {
        GameHUDInstance = CreateWidget<UUserWidget>(GetWorld(), GameHUDClass);
        if (GameHUDInstance)
        {
            GameHUDInstance->AddToViewport();
        }
    }

    // Find doors by tag
    for (int i = 1; i <= TotalRequiredLights; i++)
    {
        FString TagName = FString::Printf(TEXT("Door%d"), i);
        TArray<AActor*> FoundDoors;
        UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(*TagName), FoundDoors);

        if (FoundDoors.Num() > 0)
        {
            DoorsToOpen.Add(FoundDoors[0]);
        }
    }

    // Input mode
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        PC->SetInputMode(FInputModeGameOnly());
        PC->bShowMouseCursor = false;
    }
}

void ALostEmberGameMode::StartPlay()
{
    Super::StartPlay();
}

void ALostEmberGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bIsGameOver)
        return;

    // Timer
    CurrentTime -= DeltaSeconds;
    if (CurrentTime <= 0.0f)
    {
        CurrentTime = 0.0f;
        HandleGameOver(false);
        return;
    }
}

void ALostEmberGameMode::RegisterLightActivated()
{
    if (bIsGameOver)
        return;

    ActivatedLightCount++;

    // Open door in order
    if (DoorsToOpen.IsValidIndex(ActivatedLightCount - 1))
    {
        AActor* Door = DoorsToOpen[ActivatedLightCount - 1];
        if (Door)
        {
            Door->Destroy();
        }
    }
}

void ALostEmberGameMode::HandleGameOver(bool bPlayerWon)
{
    if (bIsGameOver)
        return;

    bIsGameOver = true;
    bIsWin = bPlayerWon;

    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        PC->SetInputMode(FInputModeUIOnly());
        PC->bShowMouseCursor = true;
    }

    if (bPlayerWon)
    {
        if (WinWidgetClass)
        {
            WinWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WinWidgetClass);
            if (WinWidgetInstance)
            {
                WinWidgetInstance->AddToViewport();
            }
        }
    }
    else
    {
        if (GameOverWidgetClass)
        {
            GameOverWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
            if (GameOverWidgetInstance)
            {
                GameOverWidgetInstance->AddToViewport();
            }
        }
    }
}