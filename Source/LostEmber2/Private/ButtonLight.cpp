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

void AButtonLight::SetState(EButtonState NewState)
{
    if (!DynMaterial)
    {
        DynMaterial = Mesh->CreateAndSetMaterialInstanceDynamic(0);
    }

    if (!DynMaterial) return;

    switch (NewState)
    {
    case EButtonState::Off:
        if (MatOff) DynMaterial->SetTextureParameterValue("BaseTexture", nullptr);
        Mesh->SetMaterial(0, MatOff);
        break;

    case EButtonState::On:
        Mesh->SetMaterial(0, MatOn);
        break;

    case EButtonState::Error:
        Mesh->SetMaterial(0, MatError);
        break;
    }
}