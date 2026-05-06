#include "ButtonSequencePuzzle.h"
#include "LightNode.h"

AButtonSequencePuzzle::AButtonSequencePuzzle()
{
    PrimaryActorTick.bCanEverTick = false;
    CurrentIndex = 0;
}

void AButtonSequencePuzzle::OnButtonPressed(int32 PressedIndex)
{
    if (!CorrectOrder.IsValidIndex(CurrentIndex))
    {
        ResetSequence();
        return;
    }

    if (CorrectOrder[CurrentIndex] == PressedIndex)
    {
        CurrentIndex++;

        if (CurrentIndex >= CorrectOrder.Num())
        {
            CompletePuzzle();
        }
    }
    else
    {
        ResetSequence();
    }
}

void AButtonSequencePuzzle::ResetSequence()
{
    CurrentIndex = 0;
}

void AButtonSequencePuzzle::CompletePuzzle()
{
    if (LinkedLightNode)
    {
        LinkedLightNode->Interact(this);
    }
}