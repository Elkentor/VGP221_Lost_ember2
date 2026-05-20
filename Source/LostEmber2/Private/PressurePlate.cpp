#include "PressurePlate.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PushableLightCube.h"
#include "UObject/ConstructorHelpers.h"

APressurePlate::APressurePlate()
{
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    TriggerBox->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	TriggerBox->SetGenerateOverlapEvents(true);

    PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
    PlateMesh->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (MeshAsset.Succeeded())
    {
        PlateMesh->SetStaticMesh(MeshAsset.Object);
    }
    
    PlateMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.1f));
    PlateMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -20.0f));
    PlateMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    bIsActivated = false;
}

void APressurePlate::BeginPlay()
{
    Super::BeginPlay();

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);
}

void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    // Cube ?
    if (Cast<APushableLightCube>(OtherActor))
    {
        bIsActivated = true;
        UE_LOG(LogTemp, Warning, TEXT("PressurePlate activated by LightCube!"));
        return;
    }

    // Joueur ?
    if (Cast<APawn>(OtherActor))
    {
        bIsActivated = true;
        UE_LOG(LogTemp, Warning, TEXT("PressurePlate activated by Player!"));
        return;
    }
}

void APressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (Cast<APushableLightCube>(OtherActor) || Cast<APawn>(OtherActor))
    {
        bIsActivated = false;
        UE_LOG(LogTemp, Warning, TEXT("PressurePlate deactivated."));
    }
}