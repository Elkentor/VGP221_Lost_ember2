#include "VictoryTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LostEmberGameMode.h"
#include "GameFramework/Pawn.h"

AVictoryTrigger::AVictoryTrigger()
{
    PrimaryActorTick.bCanEverTick = false;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECR_Overlap);

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AVictoryTrigger::OnOverlapBegin);
}

void AVictoryTrigger::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    if (!OtherActor)
        return;

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if (OtherActor != PlayerPawn)
        return;

    ALostEmberGameMode* GM = Cast<ALostEmberGameMode>(UGameplayStatics::GetGameMode(this));
    if (!GM)
        return;

	// Player reached the victory trigger, check if all lights are activated
    if (GM->GetActivatedLightCount() >= GM->GetTotalRequiredLights())
    {
        GM->HandleGameOver(true);
    }
}