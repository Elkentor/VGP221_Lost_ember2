#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightPathManager.generated.h"

class ALightPathCheckpoint;
class ALightNode;

UCLASS()
class LOSTEMBER2_API ALightPathManager : public AActor
{
    GENERATED_BODY()

public:
    ALightPathManager();

    UPROPERTY(EditAnywhere, Category = "Puzzle")
    TArray<ALightPathCheckpoint*> Checkpoints;

    UPROPERTY(EditAnywhere, Category = "Puzzle")
    ALightNode* LinkedLightNode;

    UPROPERTY(VisibleAnywhere)
    int32 CurrentIndex;

    void NotifyCheckpointHit(ALightPathCheckpoint* HitCheckpoint);

    void ResetPath();
    void CompletePath();
};