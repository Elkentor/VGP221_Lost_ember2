#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OrbCharacter.generated.h"

class IInteractable;
class USpringArmComponent;
class UCameraComponent;

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

    // --- CAMERA ---
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FollowCamera;

    // --- INTERACTION ---
    UPROPERTY(EditAnywhere, Category = "Interaction")
    float InteractionRange;

    UPROPERTY(EditAnywhere, Category = "Interaction")
    TEnumAsByte<ECollisionChannel> InteractionTraceChannel;
};