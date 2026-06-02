#include "LightPathManager.h"
#include "Kismet/GameplayStatics.h"
#include "LostEmberGameMode.h"

ALightPathManager::ALightPathManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ALightPathManager::CompletePath()
{
    ALostEmberGameMode* GM = Cast<ALostEmberGameMode>(UGameplayStatics::GetGameMode(this));
    if (GM)
    {
        GM->RegisterLightActivated();
        UE_LOG(LogTemp, Warning, TEXT("Puzzle complete: RegisterLightActivated() called."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: GameMode is not LostEmberGameMode!"));
    }
}