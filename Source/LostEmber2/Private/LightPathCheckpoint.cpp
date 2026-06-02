#include "LightPathCheckpoint.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LightPathManager.h"
#include "LostEmberGameMode.h"
#include "GameFramework/Character.h"

ALightPathCheckpoint::ALightPathCheckpoint()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;

	// Configure collision to only generate overlap events
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    BoxComponent->SetGenerateOverlapEvents(true);

    bIsFinalCheckpoint = false;
    TeleportLocation = FVector::ZeroVector;
    Manager = nullptr;
}

void ALightPathCheckpoint::NotifyActorBeginOverlap(AActor* OtherActor)
{
    ACharacter* Player = Cast<ACharacter>(OtherActor);
    if (!Player || !Manager)
        return;

	// Check if the game is already over (win condition), if so, ignore collisions
    ALostEmberGameMode* GM = Cast<ALostEmberGameMode>(UGameplayStatics::GetGameMode(this));
    if (GM && GM->IsGameOver())
        return;

	// Check if this is the final checkpoint
    if (bIsFinalCheckpoint)
    {
        Manager->CompletePath();
        UE_LOG(LogTemp, Warning, TEXT("Final checkpoint reached! Puzzle complete."));
        return;
    }

	// Teleport the player to the specified location
    Player->SetActorLocation(TeleportLocation);
    UE_LOG(LogTemp, Warning, TEXT("Player teleported to checkpoint location."));
}