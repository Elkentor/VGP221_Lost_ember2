#include "FinalDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LostEmberGameMode.h"

AFinalDoor::AFinalDoor()
{
    PrimaryActorTick.bCanEverTick = true;

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;

    RequiredLights = 3;
    OpenOffset = FVector(0.f, 0.f, 300.f);
    OpenSpeed = 2.f;
    bIsOpening = false;
}

void AFinalDoor::BeginPlay()
{
    Super::BeginPlay();

    ClosedLocation = GetActorLocation();
    TargetLocation = ClosedLocation + OpenOffset;
}

void AFinalDoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bIsOpening)
    {
        if (UWorld* World = GetWorld())
        {
            if (ALostEmberGameMode* GM = Cast<ALostEmberGameMode>(UGameplayStatics::GetGameMode(World)))
            {
                if (GM->GetActivatedLightCount() >= RequiredLights)
                {
                    bIsOpening = true;
                }
            }
        }
    }
    else
    {
        FVector NewLocation = FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, OpenSpeed);
        SetActorLocation(NewLocation);
    }
}