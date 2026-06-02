#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightPathManager.generated.h"

UCLASS()
class LOSTEMBER2_API ALightPathManager : public AActor
{
    GENERATED_BODY()

public:
    ALightPathManager();

    // Appelé par le dernier checkpoint
    UFUNCTION(BlueprintCallable)
    void CompletePath();
};