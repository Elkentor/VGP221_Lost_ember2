#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightPathCheckpoint.generated.h"

class UBillboardComponent;
class ALightPathManager;

UCLASS()
class LOSTEMBER2_API ALightPathCheckpoint : public AActor
{
    GENERATED_BODY()

public:
    ALightPathCheckpoint();

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
    int32 CheckpointIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
    ALightPathManager* Manager;
};