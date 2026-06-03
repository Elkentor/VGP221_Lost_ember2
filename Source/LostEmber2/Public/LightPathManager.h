#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightPathManager.generated.h"

class ALightPathCheckpoint;

UCLASS()
class LOSTEMBER2_API ALightPathManager : public AActor
{
    GENERATED_BODY()

public:
    ALightPathManager();

	// Called by the final checkpoint to signal that the path is complete
    UFUNCTION(BlueprintCallable)
    void CompletePath();

    // Deactivates all checkpoints after the path is complete
    UFUNCTION(BlueprintCallable)
    void DeactivateAllCheckpoints();

    // List of checkpoints assigned in the editor
    UPROPERTY(EditAnywhere, Category = "Puzzle")
    TArray<ALightPathCheckpoint*> Checkpoints;
};