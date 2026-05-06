#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "ButtonLight.generated.h"

class UStaticMeshComponent;
class AButtonSequencePuzzle;

UCLASS()
class LOSTEMBER2_API AButtonLight : public AActor, public IInteractable
{
    GENERATED_BODY()

public:
    AButtonLight();

    virtual void Interact(AActor* Interactor) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
    int32 ButtonIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
    AButtonSequencePuzzle* OwnerPuzzle;

protected:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;
};