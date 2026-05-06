#include "LightPathCheckpoint.h"
#include "Components/BillboardComponent.h"

ALightPathCheckpoint::ALightPathCheckpoint()
{
    UBillboardComponent* Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
    RootComponent = Billboard;

    CheckpointIndex = 0;
}