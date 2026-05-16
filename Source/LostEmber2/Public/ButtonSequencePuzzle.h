#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonSequencePuzzle.generated.h"

class AButtonLight;

UCLASS()
class LOSTEMBER2_API AButtonSequencePuzzle : public AActor
{
    GENERATED_BODY()

public:
    AButtonSequencePuzzle();

    UFUNCTION()
    void OnButtonPressed(int32 PressedIndex);

protected:

    UPROPERTY(EditAnywhere, Category = "Puzzle")
    TArray<int32> CorrectOrder;

    UPROPERTY(EditAnywhere, Category = "Puzzle")
    TArray<AButtonLight*> Buttons;

    int32 CurrentIndex;

    // Lock puzzle after success
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bPuzzleCompleted = false;

    void ResetSequence();
    void CompletePuzzle();
    void FlashError();
};