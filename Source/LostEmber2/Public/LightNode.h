#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "LightNode.generated.h"

class UStaticMeshComponent;
class UPointLightComponent;

UCLASS()
class LOSTEMBER2_API ALightNode : public AActor, public IInteractable
{
    GENERATED_BODY()

public:
    ALightNode();

    virtual void Interact(AActor* Interactor) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere)
    UPointLightComponent* Light;

    UPROPERTY(EditAnywhere, Category = "Light")
    bool bStartsActive;

    UPROPERTY(VisibleAnywhere, Category = "Light")
    bool bIsActivated;

    void ActivateLight();
};