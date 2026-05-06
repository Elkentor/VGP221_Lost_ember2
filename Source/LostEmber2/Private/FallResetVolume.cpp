#include "FallResetVolume.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

AFallResetVolume::AFallResetVolume()
{
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AFallResetVolume::BeginPlay()
{
    Super::BeginPlay();

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFallResetVolume::OnOverlapBegin);
}

void AFallResetVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (ACharacter* Char = Cast<ACharacter>(OtherActor))
    {
        if (RespawnPoint)
        {
            Char->SetActorLocation(RespawnPoint->GetActorLocation());
            Char->SetActorRotation(RespawnPoint->GetActorRotation());
        }
    }
}