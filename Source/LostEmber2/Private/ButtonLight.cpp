#include "ButtonLight.h"
#include "Components/StaticMeshComponent.h"
#include "ButtonSequencePuzzle.h"

AButtonLight::AButtonLight()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    ButtonIndex = 0;
    OwnerPuzzle = nullptr;
}

void AButtonLight::Interact(AActor* Interactor)
{
    if (OwnerPuzzle)
    {
        OwnerPuzzle->OnButtonPressed(ButtonIndex);
    }
}