#include "LightNode.h"
#include "LostEmberGameMode.h"
#include "Kismet/GameplayStatics.h"

ALightNode::ALightNode()
{
    PrimaryActorTick.bCanEverTick = false;
    bIsActivated = false;
}

void ALightNode::Interact(AActor* Caller)
{
    bIsActivated = true;
    UE_LOG(LogTemp, Warning, TEXT("LightNode ACTIVATED"));

    if (ALostEmberGameMode* GM = Cast<ALostEmberGameMode>(UGameplayStatics::GetGameMode(this)))
    {
        GM->RegisterLightActivated();
    }
}