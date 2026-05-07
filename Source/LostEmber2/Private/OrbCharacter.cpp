#include "OrbCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interactable.h"
#include "DrawDebugHelpers.h"

AOrbCharacter::AOrbCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Disable jumping
    GetCharacterMovement()->JumpZVelocity = 0.f;

    // --- CAMERA SETUP IN C++ ---
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // --- INTERACTION ---
    InteractionRange = 300.f;
    InteractionTraceChannel = ECC_Visibility;
}

void AOrbCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Force Unreal to use THIS camera
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (PC)
    {
        PC->SetViewTarget(this);
    }
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

    // Debug line
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.f, 0, 2.f);

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