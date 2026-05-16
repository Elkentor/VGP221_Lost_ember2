#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameInteractable.generated.h"

UINTERFACE(MinimalAPI)
class UGameInteractable : public UInterface
{
    GENERATED_BODY()
};

class LOSTEMBER2_API IGameInteractable
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void Interact(AActor* Interactor);
};