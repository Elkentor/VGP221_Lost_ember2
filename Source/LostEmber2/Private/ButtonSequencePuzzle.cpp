#include "ButtonSequencePuzzle.h"
#include "ButtonLight.h"
#include "TimerManager.h"

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
        // Mettre le bouton en vert
        if (Buttons.IsValidIndex(PressedIndex))
        {
            Buttons[PressedIndex]->SetState(EButtonState::On);
        }

        CurrentIndex++;

        if (CurrentIndex >= CorrectOrder.Num())
        {
            CompletePuzzle();
        }
    }
    else
    {
        FlashError();
    }
}

void AButtonSequencePuzzle::FlashError()
{
    for (AButtonLight* Btn : Buttons)
    {
        if (Btn)
            Btn->SetState(EButtonState::Error);
    }

    // After 0.3 sec → reset
    GetWorldTimerManager().SetTimerForNextTick([this]()
        {
            ResetSequence();
        });
}

void AButtonSequencePuzzle::ResetSequence()
{
    CurrentIndex = 0;

    for (AButtonLight* Btn : Buttons)
    {
        if (Btn)
            Btn->SetState(EButtonState::Off);
    }
}

void AButtonSequencePuzzle::CompletePuzzle()
{
	// leave it as is for now, maybe add some effects later
}