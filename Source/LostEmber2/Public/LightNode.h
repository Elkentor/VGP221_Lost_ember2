#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightNode.generated.h"

UCLASS()
class LOSTEMBER2_API ALightNode : public AActor
{
    GENERATED_BODY()

public:
    ALightNode();

    UFUNCTION(BlueprintCallable)
    void Interact(AActor* Caller);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
    bool bIsActivated;
};