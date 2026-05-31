#include "LightPathCheckpoint.h"
#include "Components/BillboardComponent.h"
#include "LightPathManager.h"

ALightPathCheckpoint::ALightPathCheckpoint()
{
    UBillboardComponent* Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
    RootComponent = Billboard;

    CheckpointIndex = 0;
    Manager = nullptr;
}

void ALightPathCheckpoint::NotifyActorBeginOverlap(AActor* OtherActor)
{
    if (Manager)
    {
        Manager->NotifyCheckpointHit(this);
    }
}