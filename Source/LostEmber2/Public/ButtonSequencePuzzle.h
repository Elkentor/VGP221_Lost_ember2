#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonSequencePuzzle.generated.h"

class ALightNode;

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

    UPROPERTY(VisibleAnywhere, Category = "Puzzle")
    int32 CurrentIndex;

    UPROPERTY(EditAnywhere, Category = "Puzzle")
    ALightNode* LinkedLightNode;

    void ResetSequence();
    void CompletePuzzle();
};