#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PushableLightCube.generated.h"

class UStaticMeshComponent;

UCLASS()
class LOSTEMBER2_API APushableLightCube : public AActor
{
    GENERATED_BODY()

public:
    APushableLightCube();

protected:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;
};