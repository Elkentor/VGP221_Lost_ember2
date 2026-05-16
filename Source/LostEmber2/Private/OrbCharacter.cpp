#include "OrbCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameInteractable.h"
#include "DrawDebugHelpers.h"

AOrbCharacter::AOrbCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    GetCharacterMovement()->JumpZVelocity = 0.f;

    bUseControllerRotationYaw = true;
    GetCharacterMovement()->bOrientRotationToMovement = false;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    InteractionRange = 500.f;
    InteractionTraceChannel = ECC_Visibility;
}

void AOrbCharacter::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PC = Cast<APlayerController>(GetController());
    if (PC)
    {
        PC->SetViewTarget(this);

        if (CrosshairClass)
        {
            UUserWidget* Crosshair = CreateWidget<UUserWidget>(PC, CrosshairClass);
            if (Crosshair)
            {
                Crosshair->AddToViewport();
            }
        }
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
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC) return;

	// Raycast from camera to determine target point
    FVector CamLoc;
    FRotator CamRot;
    PC->GetPlayerViewPoint(CamLoc, CamRot);

    FVector CamStart = CamLoc;
    FVector CamEnd = CamStart + CamRot.Vector() * InteractionRange; 
    FHitResult CamHit;
    FCollisionQueryParams CamParams;
    CamParams.AddIgnoredActor(this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        CamHit, CamStart, CamEnd, ECC_Visibility, CamParams
    );

	// If we hit something, use that point; otherwise, use the max range point
    FVector TargetPoint = bHit ? CamHit.ImpactPoint : CamEnd;

	// Raycast from player to target point
    FVector PlayerStart = GetMesh()->GetComponentLocation();
    FVector Direction = (TargetPoint - PlayerStart).GetSafeNormal();
    FVector PlayerEnd = PlayerStart + Direction * InteractionRange;

    DrawDebugLine(GetWorld(), PlayerStart, PlayerEnd, FColor::Green, false, 1.f, 0, 2.f);

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(Hit, PlayerStart, PlayerEnd, InteractionTraceChannel, Params))
    {
        AActor* HitActor = Hit.GetActor();
        if (HitActor && HitActor->GetClass()->ImplementsInterface(UGameInteractable::StaticClass()))
        {
            IGameInteractable::Execute_Interact(HitActor, this);
        }
    }
}