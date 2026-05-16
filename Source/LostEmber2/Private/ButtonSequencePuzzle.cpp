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
    // Block interaction if puzzle is completed
    if (bPuzzleCompleted)
        return;

    if (!CorrectOrder.IsValidIndex(CurrentIndex))
    {
        ResetSequence();
        return;
    }

    if (CorrectOrder[CurrentIndex] == PressedIndex)
    {
        // Turn button green
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
    if (bPuzzleCompleted)
        return;

    for (AButtonLight* Btn : Buttons)
    {
        if (Btn)
            Btn->SetState(EButtonState::Error);
    }

    // Wait 1.0 sec before resetting
    FTimerHandle ErrorTimer;
    GetWorldTimerManager().SetTimer(
        ErrorTimer,
        this,
        &AButtonSequencePuzzle::ResetSequence,
        1.0f,
        false
    );
}

void AButtonSequencePuzzle::ResetSequence()
{
    //  Do not reset if puzzle is completed
    if (bPuzzleCompleted)
        return;

    CurrentIndex = 0;

    for (AButtonLight* Btn : Buttons)
    {
        if (Btn)
            Btn->SetState(EButtonState::Off);
    }
}

void AButtonSequencePuzzle::CompletePuzzle()
{
    bPuzzleCompleted = true;

    // Keep all buttons green
    for (AButtonLight* Btn : Buttons)
    {
        if (Btn)
            Btn->SetState(EButtonState::On);
    }

    // add effects here later
}