#include "LightPathManager.h"
#include "Kismet/GameplayStatics.h"
#include "LostEmberGameMode.h"
#include "LightPathCheckpoint.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"

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

		// Desactivate all checkpoints to prevent further interactions
        DeactivateAllCheckpoints();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: GameMode is not LostEmberGameMode!"));
    }
}

void ALightPathManager::DeactivateAllCheckpoints()
{
    for (ALightPathCheckpoint* Checkpoint : Checkpoints)
    {
        if (Checkpoint && Checkpoint->BoxComponent)
        {
            Checkpoint->BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            UE_LOG(LogTemp, Warning, TEXT("Checkpoint %s collider disabled."), *Checkpoint->GetName());
        }
    }
}