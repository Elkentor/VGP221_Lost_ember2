#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

class UBoxComponent;
class ALightNode;

UCLASS()
class LOSTEMBER2_API APressurePlate : public AActor
{
    GENERATED_BODY()

public:
    APressurePlate();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* TriggerBox;

    UPROPERTY(EditAnywhere, Category = "Puzzle")
    ALightNode* LinkedLightNode;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};