#include "LightNode.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LostEmberGameMode.h"

ALightNode::ALightNode()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
    Light->SetupAttachment(RootComponent);

    bStartsActive = false;
    bIsActivated = false;
}

void ALightNode::BeginPlay()
{
    Super::BeginPlay();

    bIsActivated = bStartsActive;
    Light->SetVisibility(bIsActivated);
}

void ALightNode::Interact(AActor* Interactor)
{
    if (!bIsActivated)
    {
        ActivateLight();
    }
}

void ALightNode::ActivateLight()
{
    bIsActivated = true;
    Light->SetVisibility(true);

    if (UWorld* World = GetWorld())
    {
        if (ALostEmberGameMode* GM = Cast<ALostEmberGameMode>(UGameplayStatics::GetGameMode(World)))
        {
            GM->RegisterLightActivated();
        }
    }
}