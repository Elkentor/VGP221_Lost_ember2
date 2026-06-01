#include "LightNode.h"

ALightNode::ALightNode()
{
    PrimaryActorTick.bCanEverTick = false;
    bIsActivated = false;
}

void ALightNode::Interact(AActor* Caller)
{
    bIsActivated = true;
}