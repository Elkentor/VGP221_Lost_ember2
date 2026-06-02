#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightPathCheckpoint.generated.h"

class ALightPathManager;
class UBoxComponent;

UCLASS()
class LOSTEMBER2_API ALightPathCheckpoint : public AActor
{
    GENERATED_BODY()

public:
    ALightPathCheckpoint();

protected:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
    // --- COLLISION ---
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
    UBoxComponent* BoxComponent;

    // --- TELEPORTATION ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
    FVector TeleportLocation;

    // --- PUZZLE ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
    bool bIsFinalCheckpoint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
    ALightPathManager* Manager;
};