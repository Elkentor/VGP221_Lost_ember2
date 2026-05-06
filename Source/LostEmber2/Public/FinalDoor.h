#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinalDoor.generated.h"

class UStaticMeshComponent;

UCLASS()
class LOSTEMBER2_API AFinalDoor : public AActor
{
    GENERATED_BODY()

public:
    AFinalDoor();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* DoorMesh;

    UPROPERTY(EditAnywhere, Category = "Door")
    int32 RequiredLights;

    UPROPERTY(EditAnywhere, Category = "Door")
    FVector OpenOffset;

    UPROPERTY(EditAnywhere, Category = "Door")
    float OpenSpeed;

    bool bIsOpening;
    FVector ClosedLocation;
    FVector TargetLocation;
};