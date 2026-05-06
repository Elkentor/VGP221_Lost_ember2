#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallResetVolume.generated.h"

class UBoxComponent;

UCLASS()
class LOSTEMBER2_API AFallResetVolume : public AActor
{
    GENERATED_BODY()

public:
    AFallResetVolume();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* TriggerBox;

    UPROPERTY(EditAnywhere, Category = "Reset")
    AActor* RespawnPoint;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};