#include "OrbCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interactable.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"

AOrbCharacter::AOrbCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Désactiver le saut si tu veux
    GetCharacterMovement()->JumpZVelocity = 0.f;

    InteractionRange = 300.f;
    InteractionTraceChannel = ECC_Visibility;
}

void AOrbCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AOrbCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AOrbCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &AOrbCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &AOrbCharacter::LookUp);

    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AOrbCharacter::Interact);
}

void AOrbCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.f)
    {
        const FRotator YawRot(0.f, Controller->GetControlRotation().Yaw, 0.f);
        const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AOrbCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.f)
    {
        const FRotator YawRot(0.f, Controller->GetControlRotation().Yaw, 0.f);
        const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void AOrbCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void AOrbCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void AOrbCharacter::Interact()
{
    FVector Start;
    FRotator Rot;
    Controller->GetPlayerViewPoint(Start, Rot);
    FVector End = Start + Rot.Vector() * InteractionRange;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, InteractionTraceChannel, Params))
    {
        AActor* HitActor = Hit.GetActor();
        if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
        {
            IInteractable* Interactable = Cast<IInteractable>(HitActor);
            if (Interactable)
            {
                Interactable->Interact(this);
            }
        }
    }
}