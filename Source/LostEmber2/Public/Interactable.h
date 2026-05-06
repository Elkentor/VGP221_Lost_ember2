#pragma once

#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
    GENERATED_BODY()
};

class LOSTEMBER2_API IInteractable
{
    GENERATED_BODY()

public:
    virtual void Interact(AActor* Interactor) = 0;
};