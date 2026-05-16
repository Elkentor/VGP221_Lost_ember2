#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameInteractable.h"
#include "ButtonLight.generated.h"

class UStaticMeshComponent;
class AButtonSequencePuzzle;

UENUM(BlueprintType)
enum class EButtonState : uint8
{
    Off,
    On,
    Error
};

UCLASS()
class LOSTEMBER2_API AButtonLight : public AActor, public IGameInteractable
{
    GENERATED_BODY()

public:
    AButtonLight();

    virtual void Interact_Implementation(AActor* Interactor) override;

    void SetState(EButtonState NewState);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
    int32 ButtonIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
    AButtonSequencePuzzle* OwnerPuzzle;

    UPROPERTY(EditAnywhere, Category = "Materials")
    UMaterialInterface* MatOff;

    UPROPERTY(EditAnywhere, Category = "Materials")
    UMaterialInterface* MatOn;

    UPROPERTY(EditAnywhere, Category = "Materials")
    UMaterialInterface* MatError;

protected:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    UMaterialInstanceDynamic* DynMaterial;
};