#include "LostEmberGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ALostEmberGameMode::ALostEmberGameMode()
{
    PrimaryActorTick.bCanEverTick = true;

    ActivatedLightCount = 0;
    TotalRequiredLights = 3;

    MaxTime = 180.0f;      // 3 minutes
    CurrentTime = MaxTime;

    bIsGameOver = false;
    bIsWin = false;
}

void ALostEmberGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Reset
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
}

void ALostEmberGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bIsGameOver)
    {
        return;
    }

	// Timer
    CurrentTime -= DeltaSeconds;
    if (CurrentTime <= 0.0f)
    {
        CurrentTime = 0.0f;
		HandleGameOver(false); //Fail if time runs out
        return;
    }

	// Win condition check 
    if (ActivatedLightCount >= TotalRequiredLights)
    {
        HandleGameOver(true); // Victoire
        return;
    }
}

void ALostEmberGameMode::RegisterLightActivated()
{
    if (bIsGameOver)
    {
        return;
    }

    ActivatedLightCount++;

    // On peut checker ici aussi, au cas où
    if (ActivatedLightCount >= TotalRequiredLights)
    {
        HandleGameOver(true);
    }
}

void ALostEmberGameMode::HandleGameOver(bool bPlayerWon)
{
    if (bIsGameOver)
    {
        return; // déjà traité
    }

    bIsGameOver = true;
    bIsWin = bPlayerWon;

    // Pour l'instant : on ne change pas encore de niveau.
    // On va brancher ici plus tard le Game Over Screen / Menu.
    // Exemple plus tard :
    // UGameplayStatics::OpenLevel(this, "GameOverLevel");
}