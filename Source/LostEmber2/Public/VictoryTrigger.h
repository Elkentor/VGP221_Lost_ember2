#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VictoryTrigger.generated.h"

class UBoxComponent;

UCLASS()
class LOSTEMBER2_API AVictoryTrigger : public AActor
{
    GENERATED_BODY()

public:
    AVictoryTrigger();

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UBoxComponent* TriggerBox;

    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
};