#include "PushableLightCube.h"
#include "Components/StaticMeshComponent.h"

APushableLightCube::APushableLightCube()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    Mesh->SetSimulatePhysics(true);
}