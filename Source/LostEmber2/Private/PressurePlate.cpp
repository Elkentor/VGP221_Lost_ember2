#include "PressurePlate.h"
#include "Components/BoxComponent.h"
#include "PushableLightCube.h"

APressurePlate::APressurePlate()
{
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    TriggerBox->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
}

void APressurePlate::BeginPlay()
{
    Super::BeginPlay();

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
}

void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
	// only react if it's a LightCube
    if (Cast<APushableLightCube>(OtherActor))
    {
        UE_LOG(LogTemp, Warning, TEXT("PressurePlate triggered by LightCube!"));
    }
}