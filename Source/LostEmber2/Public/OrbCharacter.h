#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OrbCharacter.generated.h"

class IInteractable;

UCLASS()
class LOSTEMBER2_API AOrbCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AOrbCharacter();

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void LookUp(float Value);
    void Turn(float Value);

    void Interact();

    UPROPERTY(EditAnywhere, Category = "Interaction")
    float InteractionRange;

    UPROPERTY(EditAnywhere, Category = "Interaction")
    TEnumAsByte<ECollisionChannel> InteractionTraceChannel;
};