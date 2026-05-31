#include "LightPathManager.h"
#include "LightPathCheckpoint.h"
#include "LightNode.h"

ALightPathManager::ALightPathManager()
{
    PrimaryActorTick.bCanEverTick = false;
    CurrentIndex = 0;
}

void ALightPathManager::NotifyCheckpointHit(ALightPathCheckpoint* HitCheckpoint)
{
    if (!Checkpoints.IsValidIndex(CurrentIndex))
    {
        ResetPath();
        return;
    }

    if (Checkpoints[CurrentIndex] == HitCheckpoint)
    {
        CurrentIndex++;

        if (CurrentIndex >= Checkpoints.Num())
        {
            CompletePath();
        }
    }
    else
    {
        ResetPath();
    }
}

void ALightPathManager::ResetPath()
{
    CurrentIndex = 0;
}

void ALightPathManager::CompletePath()
{
    if (LinkedLightNode)
    {
        LinkedLightNode->Interact(this);
    }
}