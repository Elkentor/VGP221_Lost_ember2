#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightPathCheckpoint.generated.h"

class UBillboardComponent;

UCLASS()
class LOSTEMBER2_API ALightPathCheckpoint : public AActor
{
    GENERATED_BODY()

public:
    ALightPathCheckpoint();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
    int32 CheckpointIndex;
};